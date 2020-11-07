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

        // Gtkmm's Dispatcher lets us send signals between threads
        // this means checkForNewData will be run in the main event loop
        _dispatcher.connect(sigc::mem_fun(*this, &AudioSystem::checkForNewData));

        // The start slot will simply invoke the super class's start method
        start = sigc::mem_fun<const Device &, std::chrono::milliseconds, size_t>(*this, &Event::start);

        // The stop slot will also invoke the super's stop method
        stop = sigc::mem_fun(*this, &Event::stop);

    }

    using Event::devices;

    sigc::slot<void(const Device &, std::chrono::milliseconds, size_t)> start;
    sigc::slot<void(void)> stop;

    sigc::signal<void(const Buffer &)> newBuffer;

private:

    void notifyNewData() override {

        // This tells the main thread to check if there's a buffer's worth of new data available.
        // If there is, processNewData will be called!
        _dispatcher.emit();
    }

    void processNewData(const Buffer &buffer) override {

        // The newBuffer signal tells whatever visualizer you're using to update
        newBuffer.emit(buffer);
    }

    Glib::Dispatcher _dispatcher;

};

#endif //SPECTROGRAM_AUDIOSYSTEM_H
