#ifndef SPECTROGRAM_TEXTSPECTRUMVIEW_H
#define SPECTROGRAM_TEXTSPECTRUMVIEW_H

// TODO: THIS IS TEMPORARY
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Spectrogram/Audio/System/Blocking.h>
#include <Spectrogram/Audio/Backend/Soundio.h>
#include <Spectrogram/Audio/Backend/Dummy.h>

#include <Spectrogram/Fourier/processor.h>

#include <gtkmm/widget.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/textview.h>

using namespace Spectrogram;

class TextSpectrumView : public Gtk::ScrolledWindow {

public:

    TextSpectrumView() :
            Gtk::ScrolledWindow(),
            _system(std::make_unique<Audio::Backend::Dummy>(2000)) {

        // Add the text view to the widget
        this->add(_textView);
        _textView.set_monospace();
        _textView.show();

        // Choose a device
        auto device = _system.devices()[0];

        // Create a buffer to hold data from that device
        Audio::Buffer buffer;
        buffer.resize(device.channelCount);
        for (auto &channel : buffer)
            // Make room for exactly one second of audio
            channel.resize(device.sampleRate);

        // Read data from the device
        _system.start(device, std::chrono::seconds(2));
        _system.fillBuffer(buffer);
        _system.stop();

        // Convert that data to time domain
        _processor = Fourier::Processor(device.sampleRate);
        std::vector<Audio::Channel> timeDomainData;
        for (auto &channel : buffer)
            timeDomainData.push_back(_processor.compute(channel));

        // Add the data to the text buffer
        std::stringstream stream;
        for (size_t frequency = 0; frequency < timeDomainData[0].size(); ++frequency) {
            stream << frequency << ": ";
            for (auto &channel : timeDomainData) {
                stream << channel[frequency] << ", ";
            }
            stream << "\n";
        }
        _textView.get_buffer()->set_text(stream.str());
    }

private:

    Audio::System::Blocking _system;
    Fourier::Processor _processor;

    Gtk::TextView _textView;
};

#endif //SPECTROGRAM_TEXTSPECTRUMVIEW_H
