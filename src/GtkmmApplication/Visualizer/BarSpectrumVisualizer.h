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

    BarSpectrumVisualizer();

protected:

    void drawFrequencies(const Fourier::FrequencyDomainBuffer &buffer) override;

private:

    Gtk::Box _box;
    std::map<size_t, Gtk::LevelBar> _bars;

};


#endif //SPECTROGRAM_BARSPECTRUMVISUALIZER_H
