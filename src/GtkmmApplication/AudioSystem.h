#ifndef SPECTROGRAM_AUDIOSYSTEM_H
#define SPECTROGRAM_AUDIOSYSTEM_H

// TODO: THIS IS TEMPORARY
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Spectrogram/Audio/System/Event.h>

#include <gtkmm.h>

using namespace Spectrogram::Audio;

class AudioSystem : protected System::Event {
public:

    explicit AudioSystem(std::unique_ptr<Backend::Backend> backend) :
            Event(std::move(backend)) {
        _dispatcher.connect(sigc::mem_fun(*this, &AudioSystem::onNewDataAdded));
    }

    sigc::signal<void(const Buffer &)> newBuffer;

    void onNewDataAdded() {


        if (_channelQueues[0].read_available() > _buffer[0].size()) {

            // Fill the buffer with new data
            for (size_t sampleNumber = 0; sampleNumber < _buffer[0].size(); ++sampleNumber) {
                for (size_t channelNumber = 0; channelNumber < _buffer.size(); ++channelNumber) {

                    _buffer[channelNumber][sampleNumber] = _channelQueues[channelNumber].front();
                    _channelQueues[channelNumber].pop();
                }
            }

            // Allow the buffer to be processed
            newBuffer.emit(_buffer);
        }
    }

    void newDataNotification() override {
        _dispatcher.emit();
    }

    using Event::devices;
    using Event::start;
    using Event::stop;

private:

    Glib::Dispatcher _dispatcher;

};

#endif //SPECTROGRAM_AUDIOSYSTEM_H
