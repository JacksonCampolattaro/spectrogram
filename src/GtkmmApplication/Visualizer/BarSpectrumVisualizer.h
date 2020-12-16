//
// Created by jackcamp on 12/16/20.
//

#ifndef SPECTROGRAM_BARSPECTRUMVISUALIZER_H
#define SPECTROGRAM_BARSPECTRUMVISUALIZER_H

#include "GtkmmVisualizer.h"

#include <gtkmm/levelbar.h>
#include <gtkmm/box.h>
#include <gtkmm/levelbar.h>

using namespace Spectrogram;

class BarSpectrumVisualizer : public GtkmmVisualizer {
public:

    BarSpectrumVisualizer(size_t numBars);

protected:

    void drawFrequencies(const Fourier::FrequencyDomainBuffer &buffer) override;

private:

    double logScale(double min, double max, double value);

    Gtk::Box _box;
    std::vector<Gtk::LevelBar> _bars;
    size_t _numBars = 100;
};


#endif //SPECTROGRAM_BARSPECTRUMVISUALIZER_H
