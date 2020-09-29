//
// Created by jackcamp on 9/29/20.
//

#ifndef SPECTROGRAM_LIBRTAUDIO_H
#define SPECTROGRAM_LIBRTAUDIO_H

#include <Spectrogram/Audio/System/System.h>

#include <rtaudio/RtAudio.h>

#include <iostream>

namespace Spectrogram::Audio::System {

    class LibRtAudio : public System {
    public:

        LibRtAudio() = default;

        void setBufferSize(size_t size) override;

        Buffer getBuffer() override;

        std::vector<Device> getDevices() override;

        void setDevice(Device &device) override;

    private:

        RtAudio _rtAudio;

    };

}

#endif //SPECTROGRAM_LIBRTAUDIO_H
