#ifndef SPECTROGRAM_AUDIOSYSTEM_H
#define SPECTROGRAM_AUDIOSYSTEM_H

// TODO: THIS IS TEMPORARY
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Spectrogram/Audio/System/Event.h>

#include <gtkmm.h>

using namespace Spectrogram::Audio;

class AudioSystem : public System::Event {
public:

    explicit AudioSystem(std::unique_ptr<Backend::Backend> backend) :
            Event(std::move(backend)) {

        _dispatcher.connect(sigc::mem_fun(*this, &AudioSystem::processNewData));

        start = sigc::mem_fun<const Device &, std::chrono::milliseconds, size_t>(*this, &Event::start);
        stop = sigc::mem_fun(*this, &Event::stop);

    }

    using Event::devices;

    sigc::slot<void(const Device &, std::chrono::milliseconds, size_t)> start;
    sigc::slot<void(void)> stop;

    sigc::signal<void(const Buffer &)> newBuffer;

private:

    void notifyNewData() override {
        _dispatcher.emit();
    }

    void processNewData() override {

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

    Glib::Dispatcher _dispatcher;

};

#endif //SPECTROGRAM_AUDIOSYSTEM_H
