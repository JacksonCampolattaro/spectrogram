#ifndef SPECTROGRAM_LIBPULSEAUDIO_H
#define SPECTROGRAM_LIBPULSEAUDIO_H


#include <Spectrogram/Audio/System/System.h>

#include <pulse/pulseaudio.h>
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

    private:

        pa_simple *_pulseAudio;


    };

}


#endif //SPECTROGRAM_LIBPULSEAUDIO_H
