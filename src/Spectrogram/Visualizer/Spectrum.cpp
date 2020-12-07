#include "Spectrum.h"

#include <Spectrogram/Fourier/Transformer.h>

Spectrogram::Visualizer::Spectrum::Spectrum() : Visualizer() {}

void Spectrogram::Visualizer::Spectrum::draw(const Spectrogram::Audio::Buffer &buffer) {
    draw(Fourier::transform(buffer));
}
