#ifndef SPECTROGRAM_BACKEND_H
#define SPECTROGRAM_BACKEND_H

#include <Spectrogram/Audio/Buffer.h>
#include <Spectrogram/Audio/DeviceList.h>

#include <functional>

namespace Spectrogram::Audio::Backend {

    class Backend {
    public:

        typedef std::function<void(const std::vector<Device> &)> DevicesChangedCallback;
        typedef std::function<void(const std::vector<Sample *> &arrays, size_t length)> NewSamplesCallback;

        virtual DeviceList &devices() = 0;
        virtual void start(const Device &device, size_t frames, NewSamplesCallback callback) = 0;
        virtual void stop() = 0;

    private:

    };
}

#endif //SPECTROGRAM_BACKEND_H
