#ifndef SPECTROGRAM_FOURIER_H
#define SPECTROGRAM_FOURIER_H


namespace Fourier {

    // Take some samples of the audio stream and spit out the processed samples
    void process(double samples[], const int &inSampleSize);

}

#endif //SPECTROGRAM_FOURIER_H
