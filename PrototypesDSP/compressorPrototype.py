import numpy as np
import matplotlib.pyplot as plt

class Compressor:

    # --------------------------------------------------------------------------
    # Constructor
    def __init__(self) -> None:
        
        self.thresholdInDB      = -1
        self.ratio              = 1
        self.attackInSeconds    = 0.01
        self.releaseInSeconds   = 0.01
    
    # --------------------------------------------------------------------------
    # Processing Steps
    def averageSignal(self, detector: np.ndarray, sampleRate: int) -> np.ndarray:
        
        alphaAttack     = np.exp(-1 / (sampleRate * self.attackInSeconds))                    # Computing Attack coefficient
        alphaRelease    = np.exp(-1 / (sampleRate * self.releaseInSeconds))                   # Computing Release coefficient

        averagedSignal  = np.zeros_like(detector)                                           # Initialising output signal

        # Averager algorithm
        for n, _ in enumerate(detector):
 
            if averagedSignal[n - 1] < detector[n]:                                 
                alpha = alphaAttack
            else:
                alpha = alphaRelease

            # First order IIR equation with b0 = (1 - alpha), a0 = 1 and a1 = -alpha
            averagedSignal[n] = (1 - alpha) * detector[n] + alpha * averagedSignal[n - 1]   # Low Pass filter 
        
        return averagedSignal
    
    
    def applyStaticCurve(self, X: np.ndarray):

        G                   = np.zeros_like(X)                              # Initialising array of gain values (in dB) that will be computed
        slope               = 1 - 1/self.ratio                                   

        # Static Curve Algorithm
        for n, sample in enumerate(X):
            if sample > self.thresholdInDB:              
                G[n] = slope * (self.thresholdInDB - sample)                # Apply new slope to obtain gain value for sample if amplitude in dB is larger than threshold
            else:               
                G[n] = 0                                                    # Below threshold? Don't compute gain.
        
        return G
    

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
        ax.plot(X, thresholdPlot, linestyle = "dashed")

