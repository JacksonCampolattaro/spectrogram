#ifndef SPECTROGRAM_TEXTSPECTRUMVISUALIZER_H
#define SPECTROGRAM_TEXTSPECTRUMVISUALIZER_H

#include "SpectrumVisualizer.h"

#include <gtkmm/scrolledwindow.h>
#include <gtkmm/textview.h>

class TextSpectrumVisualizer : public SpectrumVisualizer {
public:

    TextSpectrumVisualizer();

protected:

    void draw(const Fourier::FrequencyDomainBuffer &buffer) override;

private:

    Gtk::ScrolledWindow _scrolledWindow;
    Gtk::TextView _textView;

};


#endif //SPECTROGRAM_TEXTSPECTRUMVISUALIZER_H
