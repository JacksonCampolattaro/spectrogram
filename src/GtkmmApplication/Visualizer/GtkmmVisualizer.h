#ifndef SPECTROGRAM_GTKMMVISUALIZER_H
#define SPECTROGRAM_GTKMMVISUALIZER_H

#include <Spectrogram/Visualizer/Visualizer.h>
#include <Spectrogram/Fourier/Transformer.h>

#include <sigc++/slot.h>

#include <gtkmm/bin.h>

using namespace Spectrogram;

class GtkmmVisualizer : public Visualizer::Visualizer, public Gtk::Bin {
public:

    GtkmmVisualizer();

    sigc::slot<void(const Audio::Buffer &)> slot_draw;

};


#endif //SPECTROGRAM_GTKMMVISUALIZER_H
