import librosa as lr
import numpy as np
import matplotlib.pyplot as plt

def plotSpectrogram(inputSignal: np.ndarray, sampleRate: int) -> None:

    spectrogram = lr.feature.melspectrogram(y   = inputSignal,
                                            sr  = sampleRate)
    
    _, ax = plt.subplots()
    img     = lr.display.specshow(spectrogram, 
                                  sr            = sampleRate,
                                  hop_length    = 128,
                                  n_fft         = 4096*2,
                                  x_axis        = "time",
                                  y_axis        = "mel",
                                  ax            = ax,
                                  vmin          = -10,
                                  vmax          = 10)
    ax.set_title("Spectrogram")

    plt.colorbar(img, 
                 ax         = ax)
    plt.show()