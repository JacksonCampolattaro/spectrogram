//
// Created by jackcamp on 12/6/20.
//

#include "Spectrum.h"

Spectrogram::Visualizer::Spectrum::Spectrum() : Visualizer() {}

void Spectrogram::Visualizer::Spectrum::draw(const Spectrogram::Audio::Buffer &buffer) {
    draw(Fourier::transform(buffer));
}
