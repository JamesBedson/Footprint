import numpy as np
import matplotlib.pyplot as plt

class Overdrive:

    # --------------------------------------------------------------------------
    # Constructor
    def __init__(self) -> None:

        self.thresholdInDB      = (1/3)    # threshold for symmetrical soft clipping
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
        return y

    

    def overdrive(self, x: np.ndarray, sampleRate) -> np.ndarray:
        x_peak = np.max(np.abs(x))
        x_norm = x / x_peak
        x_db = 20 * np.log10(x_norm)
        gain_linear = 10**(self.gain/20)
        level_linear = 10**(self.level/20)
        tone_linear = self.tone / sampleRate
        x_filtered = np.zeros_like(x_db)
        for i in range(1, len(x_db)):
            x_filtered[i] = x_db[i-1]*tone_linear + (1 - tone_linear)*x_filtered[i-1]
        x_pre = x_filtered * gain_linear
        x_pre_db = 20 * np.log10(x_pre)
        x_post_db = x_pre_db - self.applyStaticCurve(x_pre_db)
        x_post = level_linear * 10**(x_post_db/20)
        return x_post * x_peak
    

    # --------------------------------------------------------------------------
    # Plotting
    def plotStaticCurve(self):
        
        # numSamples  = 100
        # X           = np.linspace(-96, 0, numSamples)               # Defining input signal as linear function in log domain
        # G           = self.applyStaticCurve(X)                      # Obtain log gain values
        # Y           = X + G                                         # Adding input signal and gain together (log domain - remember?)

        # _, ax = plt.subplots(1, 1)
        # ax.set_xlabel("Input [dB]")
        # ax.xaxis.set_label_position("top")
        # ax.xaxis.set_ticks_position("top")
        # ax.set_ylim(-96, 0)
        # ax.set_xlim(-96, 0)
        # ax.set_xticks([-96, -72, -48, -24, -12, -6, 0])
        # ax.set_yticks([-96, -72, -48, -24, -12, -6, 0])
        # ax.grid(True)
        # ax.set_ylabel("Output [dB]")
        # ax.yaxis.set_label_position("right")
        # ax.yaxis.set_ticks_position("right")
        # ax.set_title("Static Overdrive Curve", fontdict= {"fontweight": "bold"})
        # ax.plot(X, Y)
        
        # thresholdPlot = [self.thresholdInDB] * numSamples
        # ax.plot(X, thresholdPlot, linestyle = "dashed")
        numSamples = 1000
        x = np.linspace(-1, 1, numSamples)
        y = self.applyStaticCurve(x)
        fig, ax = plt.subplots()
        ax.plot(x, y)
        ax.set_xlabel('Input signal')
        ax.set_ylabel('Output signal')
        ax.set_title('Static Curve')
        plt.show()


