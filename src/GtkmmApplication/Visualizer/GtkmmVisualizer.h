#ifndef SPECTROGRAM_GTKMMVISUALIZER_H
#define SPECTROGRAM_GTKMMVISUALIZER_H

#include <Spectrogram/Visualizer/Spectrum.h>

#include <sigc++/slot.h>

#include <gtkmm/bin.h>

using namespace Spectrogram;

class GtkmmVisualizer : public Visualizer::Spectrum, public Gtk::Bin {
public:

    GtkmmVisualizer();

    sigc::slot<void(const Audio::Buffer &)> slot_draw;

};


#endif //SPECTROGRAM_GTKMMVISUALIZER_H