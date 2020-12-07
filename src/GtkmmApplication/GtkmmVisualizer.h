#ifndef SPECTROGRAM_GTKMMVISUALIZER_H
#define SPECTROGRAM_GTKMMVISUALIZER_H

#include <Spectrogram/Visualizer/Visualizer.h>

#include <sigc++/slot.h>

#include <gtkmm/bin.h>

using namespace Spectrogram;

class GtkmmVisualizer : private Visualizer::Visualizer, public Gtk::Bin {
public:

    GtkmmVisualizer();

    sigc::slot<void(const Audio::Buffer &)> slot_draw;

protected:

    void draw(const Audio::Buffer &buffer) override;

};


#endif //SPECTROGRAM_GTKMMVISUALIZER_H
