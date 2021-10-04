//
// Created by jackcamp on 10/4/21.
//

#ifndef SPECTROGRAM_SPECTROGRAMVISUALIZER_H
#define SPECTROGRAM_SPECTROGRAMVISUALIZER_H

#include "GtkmmVisualizer.h"

#include <gtkmm/drawingarea.h>

using namespace Spectrogram;

class SpectrogramVisualizer : public GtkmmVisualizer {
public:

    SpectrogramVisualizer();

protected:

    void drawFrequencies(const Fourier::FrequencyDomainBuffer &buffer) override;

    bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;

private:

    static double inverseLogScale(std::pair<double, double> input_range, std::pair<double, double> output_range,
                                  double input_value);

    Gtk::DrawingArea _drawingArea;

    Cairo::RefPtr<Cairo::ImageSurface> _surface;
};


#endif //SPECTROGRAM_SPECTROGRAMVISUALIZER_H
