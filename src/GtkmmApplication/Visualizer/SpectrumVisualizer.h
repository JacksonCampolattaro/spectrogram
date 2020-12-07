#ifndef SPECTROGRAM_SPECTRUMVISUALIZER_H
#define SPECTROGRAM_SPECTRUMVISUALIZER_H

#include "GtkmmVisualizer.h"

#include <Spectrogram/Fourier/Transformer.h>

class SpectrumVisualizer : public GtkmmVisualizer {
public:

    SpectrumVisualizer();

protected:

    void draw(const Audio::Buffer &buffer) override;

    virtual void draw(const Fourier::FrequencyDomainBuffer &buffer) = 0;

};


#endif //SPECTROGRAM_SPECTRUMVISUALIZER_H
