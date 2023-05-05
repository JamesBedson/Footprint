import numpy as np
import matplotlib.pyplot as plt
from scipy import signal


class Distortion:

    # --------------------------------------------------------------------------
    # Constructor
    def __init__(self) -> None:

        self.gain           = 6      #dB
        self.tone           = 0.5    #Hz
        self.level          = 0.5    #dB
        self.alpha          = 50
        # --------------------------------------------------------------------------
    # Processing Steps
    '''
        # Amplitude Detector Function
    def getAmplitudeEnvelope(self, x: np.ndarray, sampleRate: int):

        #detector = np.abs(x)

        b, a = self.getLPFCoefficients(sampleRate       = sampleRate,
                                       cutoffFrequency  = 1000,
                                       q                = 1)

        return signal.lfilter(b, a, x)
    

    # For more info on filter coefficients, go to https://webaudio.github.io/Audio-EQ-Cookbook/audio-eq-cookbook.html
    def getLPFCoefficients(self, sampleRate: int, cutoffFrequency: float, q:float) -> tuple[list, list]:
        
        w       = 2 * np.pi * (cutoffFrequency/sampleRate)
        alpha   = np.sin(w) / (2 * q)

        b0 = (1 - np.cos(w))/2
        b1 = 1 - np.cos(w)
        b2 = b0
        a0 = 1 + alpha
        a1 = -2 * np.cos(w)
        a2 = 1 - alpha

        b = [b0, b1, b2]
        a = [a0, a1, a2]

        # Normalise coefficients
        b = b / a[0]
        a = a / a[0]
    
        return b, a'''

    def applyHardClipping(self, x: np.ndarray):
        
        y       = np.zeros_like(x)
        xHat    = np.abs(x)
        
        for n, _ in enumerate(x):
            y[n] = -(xHat[n] - 1)**self.alpha + 1
            if x[n] < 0:
                y[n] *= -1
        return y
    
    def applyDistortion(self, x: np.ndarray) -> np.ndarray:
        
        y = np.power(10, self.gain/20) * x
        return self.applyHardClipping(y)
    
    
    def plotStaticCurveLinear(self):

        numSamples = 10000
        x = np.linspace(-1, 1, numSamples)      
        y = self.applyHardClipping(x)           
        
        _, ax = plt.subplots()  
        ax.plot(x, y, linewidth = 5)
        ax.set_xlabel('Input signal')
        ax.set_ylabel('Output signal')
        ax.set_title('Static Curve')
        ax.grid(True)
        

    def plotStaticCurveDecibel(self):
        numSamples = 10000
        x = np.linspace(-1, 1, numSamples)      
        y = self.applyHardClipping(x)           
        X = 20 * np.log10(np.abs(x))
        Y = 20 * np.log10(np.abs(y))
        
        _, ax = plt.subplots()  
        ax.plot(X, Y, linewidth = 5)
        ax.set_xlabel('Input signal (dB)')
        ax.set_ylabel('Output signal (dB)')
        ax.set_title('Static Curve')
        ax.grid(True)