#ifndef SPECTROGRAM_TEXTSPECTRUMVIEW_H
#define SPECTROGRAM_TEXTSPECTRUMVIEW_H

// TODO: THIS IS TEMPORARY
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Spectrogram/Fourier/processor.h>

#include <gtkmm/widget.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/textview.h>

using namespace Spectrogram;

class TextSpectrumView : public Gtk::ScrolledWindow {

public:

    TextSpectrumView() :
            Gtk::ScrolledWindow() {

        // Add the text view to the widget
        this->add(_textView);
        _textView.set_monospace();
        _textView.show();

        on_newBuffer = sigc::mem_fun(*this, &TextSpectrumView::drawBuffer);

    }

    sigc::slot<void(const Audio::Buffer &)> on_newBuffer;

    void drawBuffer(const Audio::Buffer &buffer) {

        // Convert data to time domain
        _processor = Fourier::Processor(buffer[0].size());
        std::vector<Audio::Channel> timeDomainData;
        for (auto &channel : buffer)
            timeDomainData.push_back(_processor.compute(channel));

        // Add the data to the text buffer
        std::stringstream stream;
        for (size_t frequency = 0; frequency < timeDomainData[0].size(); frequency += 1) {
            stream << frequency << ":\t";
            for (auto &channel : timeDomainData) {

                float normalizedAmplitude = (90.0f + channel[frequency]) / 90.0f;

                stream << "[";

                const int width = 10;
                for (int i = 0; i < width; ++i) {
                    stream << ((int) (normalizedAmplitude * width) > i ? '|' : ' ');
                }

//                stream << normalizedAmplitude;

                stream << "] ";
            }
            stream << "\n";
        }
        _textView.get_buffer()->set_text(stream.str());
    }

private:

    Fourier::Processor _processor;

    Gtk::TextView _textView;
};

#endif //SPECTROGRAM_TEXTSPECTRUMVIEW_H
