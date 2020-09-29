#ifndef SPECTROGRAM_LIBPORTAUDIO_H
#define SPECTROGRAM_LIBPORTAUDIO_H

#include <Spectrogram/Audio/System/System.h>

#include <portaudio.h>

#include <iostream>

namespace Spectrogram::Audio::System {

    class LibPortAudio : public System {
    public:

        LibPortAudio();

        void setBufferSize(size_t size) override;

        Buffer getBuffer() override;

        std::vector<Device> getDevices() override;

        void setDevice(Device &device) override;
    };

}


#endif //SPECTROGRAM_LIBPORTAUDIO_H
