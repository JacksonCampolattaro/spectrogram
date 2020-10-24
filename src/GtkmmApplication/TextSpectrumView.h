#ifndef SPECTROGRAM_TEXTSPECTRUMVIEW_H
#define SPECTROGRAM_TEXTSPECTRUMVIEW_H

// TODO: THIS IS TEMPORARY
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Spectrogram/Fourier/processor.h>
#include <Spectrogram/Audio/DeviceList.h>

#include <gtkmm/widget.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/textview.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>

using namespace Spectrogram;

class TextSpectrumView : public Gtk::Box {

public:

    TextSpectrumView() :
            Gtk::Box(Gtk::ORIENTATION_VERTICAL) {

        // Add the scrolled window containing the text
        this->pack_start(_scrolledWindow);
        _scrolledWindow.show();

        // Add the text view
        _scrolledWindow.add(_textView);
        _textView.set_monospace();
        _textView.show();

        // Add the device dropdown
        this->pack_start(_comboBoxDevices, false, false);
        _comboBoxDevices.show();

        // Add the start button
        this->pack_start(_buttonStart, false, false);
        _buttonStart.show();
        _buttonStart.signal_clicked().connect(
                [this] {

                    const Audio::Device &device = (*_devices)[_comboBoxDevices.get_active_row_number()];
                    start.emit(
                            device,
                            std::chrono::seconds(2),
                            device.sampleRate
                    );
                }
        );

        on_newBuffer = sigc::mem_fun(*this, &TextSpectrumView::drawBuffer);

    }

    sigc::signal<void(const Audio::Device &, std::chrono::milliseconds, size_t)> start;
    sigc::signal<void(void)> stop;

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

    void setDevices(const Audio::DeviceList &devices) {

        _devices = &devices;

        for (auto &device : devices) {
            _comboBoxDevices.append(device.name);
            if (device.isDefault)
                _comboBoxDevices.set_active(device.id);
        }
    }

private:

    Fourier::Processor _processor;

    Gtk::ScrolledWindow _scrolledWindow;
    Gtk::TextView _textView;
    Gtk::Button _buttonStart{"start"};

    const Audio::DeviceList *_devices{};
    Gtk::ComboBoxText _comboBoxDevices;
};

#endif //SPECTROGRAM_TEXTSPECTRUMVIEW_H
