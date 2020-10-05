#ifndef SPECTROGRAM_BACKEND_H
#define SPECTROGRAM_BACKEND_H

#include <Spectrogram/Audio/Buffer.h>
#include <Spectrogram/Audio/Device.h>

#include <functional>

namespace Spectrogram::Audio::Backend {

    class Backend {
    public:

        typedef Sample Sample;
        typedef Buffer Buffer;

        typedef std::function<void(const std::vector<Device> &)> DevicesChangedCallback;
        typedef std::function<void(Buffer)> NewBufferCallback;

        virtual std::vector<Device> &devices() = 0;
        virtual void start(Device device, NewBufferCallback callback) = 0;
        virtual void stop() = 0;

    private:

        DevicesChangedCallback _devicesChanged;

    };
}

#endif //SPECTROGRAM_BACKEND_H
