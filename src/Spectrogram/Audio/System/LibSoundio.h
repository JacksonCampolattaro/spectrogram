#ifndef SPECTROGRAM_LIBSOUNDIO_H
#define SPECTROGRAM_LIBSOUNDIO_H

#include <Spectrogram/Audio/System/System.h>

#include <soundio/soundio.h>

#include <iostream>

namespace Spectrogram::Audio::System {

    class LibSoundio : public System {
    public:

        LibSoundio();
        ~LibSoundio();

        void setBufferSize(size_t size) override;

        Buffer getBuffer() override;

        std::vector<Device> getDevices() override;

    private:

        SoundIo *_soundio;

    };

}


#endif //SPECTROGRAM_LIBSOUNDIO_H
