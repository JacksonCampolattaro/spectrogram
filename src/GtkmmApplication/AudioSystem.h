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

        _dispatcher.connect(sigc::mem_fun(*this, &AudioSystem::checkForNewData));

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

    void processNewData(const Buffer &buffer) override {

        // Allow the buffer to be processed
        newBuffer.emit(buffer);
    }

    Glib::Dispatcher _dispatcher;

};

#endif //SPECTROGRAM_AUDIOSYSTEM_H
