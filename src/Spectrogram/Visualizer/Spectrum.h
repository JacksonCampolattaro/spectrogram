#ifndef SPECTROGRAM_SPECTRUM_H
#define SPECTROGRAM_SPECTRUM_H

#include <Spectrogram/Visualizer/Visualizer.h>
#include <Spectrogram/Fourier/FrequencyDomainBuffer.h>
#include <Spectrogram/Fourier/Transformer.h>

namespace Spectrogram::Visualizer {

    class Spectrum : protected Visualizer {
    public:

        Spectrum();

    protected:

        void draw(const Audio::Buffer &buffer) override;

        virtual void draw(const Fourier::FrequencyDomainBuffer &buffer) = 0;

    };

}


#endif //SPECTROGRAM_SPECTRUM_H
