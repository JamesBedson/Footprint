import numpy as np
import matplotlib.pyplot as plt

class Reverb:

    # --------------------------------------------------------------------------
    # Constructor
    def __init__(self) -> None:
        
        self.mix = 0.5
        self.fs       = 44100

    def plotIR(self, x: np.ndarray):

        time = np.linspace(0, len(x) / self.fs, num = len(x))

        # Plot audio file against time array
        plt.plot(time, x)
        plt.xlabel('Time (s)')
        plt.ylabel('Amplitude')
        plt.show()



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
        output          = self.mix*0.3  * output + x_zp
        print(self.mix*0.3)
        return output