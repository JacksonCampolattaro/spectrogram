//
// Created by jackcamp on 12/6/20.
//

#include "SpectrumVisualizer.h"

SpectrumVisualizer::SpectrumVisualizer() : GtkmmVisualizer() {}

void SpectrumVisualizer::draw(const Audio::Buffer &buffer) {
    draw(Fourier::transform(buffer));
}
