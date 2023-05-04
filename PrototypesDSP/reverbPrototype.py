import numpy as np
import matplotlib.pyplot as plt

class Reverb:

    # --------------------------------------------------------------------------
    # Constructor
    def __init__(self) -> None:
        
        self.mix      = 0.5

    def plotIR(self, x: np.ndarray):
        plt.plot(x)


    # --------------------------------------------------------------------------
    # roll array x by k elements & zero out the last k elements of x
    def roll_zero(self, x: np.ndarray, k: int) -> np.ndarray:

        result = x[k:]
        result = np.append(x[k:], np.zeros(k))
        return   result


    # --------------------------------------------------------------------------
    # zero padding the array with k 0's at the end
    def zero_pad(self, x: np.ndarray, k: int) -> np.ndarray:

        return np.append(x, np.zeros(k))
    

    # --------------------------------------------------------------------------
    # partition impulse response and precompute frequency response for each block
    def precompute_frequency_responses(self, h: np.ndarray, L: int, k: int, num_blocks: int) -> np.ndarray:

        H           = np.zeros((num_blocks, L+k)).astype('complex128')

        for j in range(num_blocks):
            H[j]   += np.fft.fft(self.zero_pad(h[j*k: (j+1)*k], L))

        return H
    

    # --------------------------------------------------------------------------
    # Frequency Domain Delay Line
    # Do Overlap Add in Frequency Domain
    def fdl(self, x: np.ndarray, h: np.ndarray) -> np.ndarray:
        L = 2**8 #signal block size
        p = len(h)
        k = L # ir block size

        num_ir_blocks       = int(p/k)
        num_sig_blocks      = int(len(x) / L)
        H                   = self.precompute_frequency_responses(h, L, k, num_ir_blocks)
        fdl                 = np.zeros(2*L*num_ir_blocks).astype('complex128')
        output              = np.zeros(p+len(x)-1).astype('float64')
        out                 = np.zeros(2*L-1)

        for i in range(num_sig_blocks):
            input_buffer    = x[i*L: (i+1)*L]
            spectrum        = np.fft.fft(self.zero_pad(input_buffer, L))
            
            for j in range(num_ir_blocks):
                fdl[j*2*L: (j+1)*2*L] += H[j] * spectrum

            out                    += np.fft.ifft(fdl[:2*L]).real[:2*L-1]
            output[i*L:(i+1)*L]    += out[:L]
            fdl                     = self.roll_zero(fdl, 2*L)
            out                     = self.roll_zero(out, L)
        
        for i in range(1, num_ir_blocks): #process remaining frequency blocks
            out            += np.fft.ifft(fdl[:2*L]).real[:2*L-1]
            output[num_sig_blocks+i*L: num_sig_blocks+(i+1)*L] += out[:L]
            out             = self.roll_zero(out, L)
            fdl             = self.roll_zero(fdl, 2*L)

        x_zp            = self.zero_pad(x, p-1)
        output          = self.mix  * output + x_zp
        return output
    
    
    '''def applyStaticCurve(self, X: np.ndarray):

        G                   = np.zeros_like(X)                              # Initialising array of gain values (in dB) that will be computed
        slope               = 1 - 1/self.ratio                                   

        # Static Curve Algorithm
        for n, sample in enumerate(X):
            if sample > self.thresholdInDB:              
                G[n] = slope * (self.thresholdInDB - sample)                # Apply new slope to obtain gain value for sample if amplitude in dB is larger than threshold
            else:               
                G[n] = 0                                                    # Below threshold? Don't compute gain.
        
        return G'''
    
"""
    def compress(self, x: np.ndarray, sampleRate) -> np.ndarray:

        detector            = np.abs(x)                                     # Apply detector function (absolute value, square...)
        
        # Block 1
        xPeak               = self.averageSignal(detector, sampleRate)      # Average the peaks (with first order low pass)
        
        # Block 2
        xPeak[xPeak <= 0]   = np.finfo(float).eps                           # Handling log
        X                   = 20 * np.log10(xPeak)                          # Converting to decibels
        G                   = self.applyStaticCurve(X)                      # Obtain the new gain values in decibels
        
        # Block 3
        g                   = np.power(10, G/20)                          # Convert to linear
        g                   = self.averageSignal(g, sampleRate)             # Average the new gain values (with first order filter) 

        return x * g
    

    # --------------------------------------------------------------------------
    # Plotting
    def plotStaticCurve(self):
        
        numSamples  = 100
        X           = np.linspace(-96, 0, numSamples)               # Defining input signal as linear function in log domain
        G           = self.applyStaticCurve(X)                      # Obtain log gain values
        Y           = X + G                                         # Adding input signal and gain together (log domain - remember?)

        _, ax = plt.subplots(1, 1)
        ax.set_xlabel("Input [dB]")
        ax.xaxis.set_label_position("top")
        ax.xaxis.set_ticks_position("top")
        ax.set_ylim(-96, 0)
        ax.set_xlim(-96, 0)
        ax.set_xticks([-96, -72, -48, -24, -12, -6, 0])
        ax.set_yticks([-96, -72, -48, -24, -12, -6, 0])
        ax.grid(True)
        ax.set_ylabel("Output [dB]")
        ax.yaxis.set_label_position("right")
        ax.yaxis.set_ticks_position("right")
        ax.set_title("Static Compresor Curve", fontdict= {"fontweight": "bold"})
        ax.plot(X, Y)
        
        thresholdPlot = [self.thresholdInDB] * numSamples
        ax.plot(X, thresholdPlot, linestyle = "dashed") """