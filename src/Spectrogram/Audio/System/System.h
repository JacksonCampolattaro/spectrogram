#ifndef SPECTROGRAM_SYSTEM_H
#define SPECTROGRAM_SYSTEM_H

#include <Spectrogram/Audio/Buffer.h>
#include <Spectrogram/Audio/Device.h>

namespace Spectrogram::Audio {

    class System {
    public:

        virtual void setBufferSize(size_t size) = 0;

        virtual Buffer getBuffer() = 0;

        virtual std::vector<Device> getDevices() = 0;

    };
}

#endif //SPECTROGRAM_SYSTEM_H
