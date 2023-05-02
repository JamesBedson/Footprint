import numpy as np
import matplotlib.pyplot as plt
from scipy import signal


class Overdrive:

    # --------------------------------------------------------------------------
    # Constructor
    def __init__(self) -> None:

        self.threshold      = (1/3)    # threshold for symmetrical soft clipping
        self.gain           = 6      #dB
        self.tone           = 0.5    #Hz
        self.level          = 0.5    #dB
    
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
        x = self.applyStaticCurve(x)

        # Convert dB gain to linear gain
        gain_lin = 10**(self.gain/20)

        # Calculate overdrive threshold as a fraction of the maximum signal amplitude
        max_amp = np.abs(x).max()
        overdrive_threshold = max_amp * self.threshold

        # Apply soft clipping
        x_overdriven = np.sign(x) * (1 - np.exp(-np.abs(x/gain_lin))) / (1 - np.exp(-1/gain_lin))
        x_overdriven *= overdrive_threshold / np.abs(x_overdriven).max()
        
        return x_overdriven

    

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

    def signal_stft(signal, window, hop_size):
        sample_rate = 44100
        """
        Computes the Short-Time Fourier Transform (STFT) of a signal.
        
        Parameters:
        - signal (np.ndarray): Input signal.
        - window (np.ndarray): Window function to use.
        - hop_size (int): Hop size of the FFT window.
        
        Returns:
        - f (np.ndarray): Array of frequency values.
        - t (np.ndarray): Array of time values.
        - Zxx (np.ndarray): STFT matrix.
        """
        
        # Calculate the STFT of the signal
        n_frames = int(np.ceil(len(signal) / hop_size))
        padded_size = (n_frames - 1) * hop_size + len(window)
        padded_signal = np.zeros(padded_size)
        padded_signal[:len(signal)] = signal
        f = np.fft.rfftfreq(len(window))
        t = np.arange(n_frames) * hop_size / float(sample_rate)
        Zxx = np.zeros((len(f), n_frames), dtype=np.complex)
        
        for i in range(n_frames):
            frame_start = i * hop_size
            frame_end = frame_start + len(window)
            frame = padded_signal[frame_start:frame_end] * window
            Zxx[:, i] = np.fft.rfft(frame)
            
        return f, t, Zxx  
    def plot_spectrogram(signal, sample_rate, window_size=1024, hop_size=512, window_type='hann', cmap='viridis'):
        """
        Computes and plots the spectrogram of a signal.
        
        Parameters:
        - signal (np.ndarray): Input signal.
        - sample_rate (int): Sample rate of the signal.
        - window_size (int): Size of the FFT window. Default is 1024.
        - hop_size (int): Hop size of the FFT window. Default is 512.
        - window_type (str): Type of window function to use. Default is 'hann'.
        - cmap (str): Colormap to use. Default is 'viridis'.
        """
        
        # Calculate the STFT of the signal
        window = np.get_window(window_type, window_size)
        f, t, Zxx = Overdrive.signal_stft(signal, window, hop_size)
        
        # Convert the magnitude of the STFT to dB scale
        Zxx = 20 * np.log10(np.abs(Zxx))
        
        # Plot the spectrogram
        plt.figure(figsize=(12, 6))
        plt.imshow(Zxx, aspect='auto', origin='lower', cmap=cmap, extent=[t.min(), t.max(), f.min(), f.max()])
        plt.xlabel('Time (s)')
        plt.ylabel('Frequency (Hz)')
        plt.title('Spectrogram')
        plt.colorbar()
        plt.show()
