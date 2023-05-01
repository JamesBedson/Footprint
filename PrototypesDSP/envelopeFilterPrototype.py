import numpy as np
import matplotlib.pyplot as plt
import scipy.signal

class EnvelopeFilter:

    # Constructor
    def __init__(self) -> None:
        
        self.q              = 1
        self.sensitivity    = 0.5


    # Amplitude Detector Function
    def getAmplitudeEnvelope(self, x: np.ndarray, sampleRate: int):

        detector = np.abs(x)

        b, a = self.getLPFCoefficients(sampleRate       = sampleRate, 
                                       cutoffFrequency  = 1000,
                                       q                = 1)
        
        b = b / a[0]
        a = a / a[0]

        return scipy.signal.lfilter(b, a, detector)
    

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
    
        return b, a
    

    def process(self, x: np.ndarray, sampleRate: int):
        
        # Step 1: Compute Amplitude Envelope of the signal
        amp = self.getAmplitudeEnvelope(x           = x, 
                                        sampleRate  = sampleRate)
        
        
        thresholdMinFreq    = 100                   # define minimum cutoff frequency
        nyquist             = sampleRate // 2       # define maximum cutoff frequency 
        y                   = np.zeros_like(x)      # initialise output


        # Step 2: Define parameters for moving average to smooth out the cutoff frequencies
        windowSize          = 800                   # Arbitrary. Higher window size --> Less filter distortion
        window              = []                    # Initialise window array
        filteredCutOffFreq  = []                    # Initialise array for storing the cutoff frequencies

        for n, _ in enumerate(amp):

            # Step 3: Compute new cutoff frequency of the filter (Amplitude Modulation)
            currentAmp          = amp[n]
            currentCutoffFreq   = float(thresholdMinFreq + self.sensitivity * currentAmp * (nyquist - thresholdMinFreq))
            window.append(currentCutoffFreq)

            if len(window) > windowSize:
                window.pop(0)
            
            averageCutoffFreq   = np.mean(window)
            filteredCutOffFreq.append(averageCutoffFreq)

            # Step 4: Compute coefficients of low pass filter with the new cutoff frequency 
            b, a                = self.getLPFCoefficients(sampleRate        = sampleRate,
                                                          cutoffFrequency   = averageCutoffFreq, #type: ignore
                                                          q                 = self.q)
            
            # Normalise coefficients
            b = b / a[0]
            a = a / a[0]
            
            if n == 0 or n == 1:    # Handling edge case
                xN = 0
                xN1 = 0
                xN2 = 0
            else:
                xN = x[n]
                xN1 = x[n - 1]
                xN2 = x[n - 2]

            # Step 5: Apply IIR filter equation using the newly obtained coefficients
            y[n] = b[0] * xN + b[1] * xN1 + b[2] * xN2 - a[1] * y[n - 1] - a[2] * y[n - 2]
            
        return y
