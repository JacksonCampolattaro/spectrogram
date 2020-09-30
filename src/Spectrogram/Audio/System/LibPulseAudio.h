#ifndef SPECTROGRAM_LIBPULSEAUDIO_H
#define SPECTROGRAM_LIBPULSEAUDIO_H


#include <Spectrogram/Audio/System/System.h>

#include <pulse/simple.h>

#include <iostream>

namespace Spectrogram::Audio::System {

    class LibPulseAudio : public System {
    public:

        LibPulseAudio();

        void setBufferSize(size_t size) override;

        Buffer getBuffer() override;

        std::vector<Device> getDevices() override;

        void setDevice(Device &device) override;

        // TODO
    };

}


#endif //SPECTROGRAM_LIBPULSEAUDIO_H
