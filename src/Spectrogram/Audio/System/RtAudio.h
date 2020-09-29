//
// Created by jackcamp on 9/29/20.
//

#ifndef SPECTROGRAM_RTAUDIO_H
#define SPECTROGRAM_RTAUDIO_H

#include <Spectrogram/Audio/System/System.h>

#include <rtaudio/RtAudio.h>

#include <iostream>

namespace Spectrogram::Audio::System {

    class RtAudio : public System {

    public:
        void setBufferSize(size_t size) override;

        Buffer getBuffer() override;

        std::vector<Device> getDevices() override;

    };

}

#endif //SPECTROGRAM_RTAUDIO_H
