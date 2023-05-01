import numpy as np
import matplotlib.pyplot as plt
from scipy import signal


class Overdrive:

    # --------------------------------------------------------------------------
    # Constructor
    def __init__(self) -> None:

        self.threshold      = (1/3)    # threshold for symmetrical soft clipping
        self.gain       = 6                #dB
        self.tone            = 0.5         #Hz
        self.level     = 0.5               #dB
    
    # --------------------------------------------------------------------------
    # Processing Steps
    def applyStaticCurve(self, x: np.ndarray):
        # input x is a numpy array
        N = len(x)
        th = 1/3 # threshold for symmetrical soft clipping by Schetzen Formula
        y = np.zeros_like(x)
        for i in range(N):
            if abs(x[i]) < th:
                y[i] = 2*x[i]
            elif abs(x[i]) >= th and abs(x[i]) <= 2*th:
                if x[i] > 0:
                    y[i] = (3 - (2 - x[i]*3)**2) / 3
                else:
                    y[i] = -(3 - (2 - abs(x[i])*3)**2) / 3
            else:
                if x[i] > 0:
                    y[i] = 1
                else:
                    y[i] = -1
        return y  # output y is a numpy array

    

    def overdrive_(self, x: np.ndarray, sampleRate) -> np.ndarray:
        """
        Apply overdrive distortion to a signal.

        Args:
        - signal: array-like, input audio signal
        - gain: float, gain amount in dB
        - threshold: float, overdrive threshold as a fraction of the maximum signal amplitude

        Returns:
        - array-like, output distorted signal
        """
    
        # Convert dB gain to linear gain
        gain_lin = 10**(self.gain/20)

        # Calculate overdrive threshold as a fraction of the maximum signal amplitude
        max_amp = np.abs(x).max()
        overdrive_threshold = max_amp * self.threshold

        # Apply soft clipping
        x_overdriven = np.sign(x) * (1 - np.exp(-np.abs(x/gain_lin))) / (1 - np.exp(-1/gain_lin))
        x_overdriven *= overdrive_threshold / np.abs(x_overdriven).max()
        
        return x_overdriven


        # x_peak = np.max(np.abs(x))  # peak value of input signal
        # x_norm = x / x_peak       # normalized input signal
        # x_db = 20 * np.log10(x_norm)  # input signal in dB
        # gain_linear = 10**(self.gain/20)  # linear gain
        # level_linear = 10**(self.level/20)  # linear level
        # tone_linear = self.tone / sampleRate  # linear tone
        # x_filtered = np.zeros_like(x_db)    # filtered input signal
        # for i in range(1, len(x_db)):  # first sample is not filtered
        #     x_filtered[i] = x_db[i-1]*tone_linear + (1 - tone_linear)*x_filtered[i-1]   # first order lowpass filter
        # x_pre = x_filtered * gain_linear  # pre-gain signal
        # x_pre_db = 20 * np.log10(x_pre)  # pre-gain signal in dB
        # x_post_db = x_pre_db - self.applyStaticCurve(x_pre_db)  # post-gain signal in dB
        # x_post = level_linear * 10**(x_post_db/20)  # post-gain signal
        # return x_post * x_peak  # post-gain signal in time domain

    

    # --------------------------------------------------------------------------
    # Plotting
    def plotStaticCurve(self):

        numSamples = 10000
        x = np.linspace(-1, 1, numSamples)  # input signal
        y = self.applyStaticCurve(x) # output signal
        fig, ax = plt.subplots()  
        ax.plot(x, y)
        ax.set_xlabel('Input signal')
        ax.set_ylabel('Output signal')
        ax.set_title('Static Curve')
        plt.show()

    def plotsecondStaticCurve(self):
        numSamples = 10000
        x = np.linspace(-1, 1, numSamples)  # input signal
        y = self.applyStaticCurve(x) # output signal
        x_db = 20 * np.log10(np.abs(x))
        y_db = 20 * np.log10(np.abs(y))
        fig, ax = plt.subplots()  
        ax.plot(x_db, y_db)
        ax.set_xlabel('Input signal (dB)')
        ax.set_ylabel('Output signal (dB)')
        ax.set_title('Static Curve')
        plt.show()

