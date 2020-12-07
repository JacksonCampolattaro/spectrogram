#ifndef SPECTROGRAM_TEXTSPECTRUMVISUALIZER_H
#define SPECTROGRAM_TEXTSPECTRUMVISUALIZER_H

#include "GtkmmVisualizer.h"

#include <gtkmm/scrolledwindow.h>
#include <gtkmm/textview.h>

using namespace Spectrogram;

class TextSpectrumVisualizer : public GtkmmVisualizer {
public:

    TextSpectrumVisualizer();

protected:

    void drawFrequencies(const Fourier::FrequencyDomainBuffer &buffer) override;

private:

    Gtk::ScrolledWindow _scrolledWindow;
    Gtk::TextView _textView;

};


#endif //SPECTROGRAM_TEXTSPECTRUMVISUALIZER_H
