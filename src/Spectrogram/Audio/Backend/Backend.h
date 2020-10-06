#ifndef SPECTROGRAM_BACKEND_H
#define SPECTROGRAM_BACKEND_H

#include <Spectrogram/Audio/Buffer.h>
#include <Spectrogram/Audio/DeviceList.h>

#include <functional>

namespace Spectrogram::Audio::Backend {

    template <class Interface>
    class Backend : public Interface {
    public:

        typedef Sample Sample;
        typedef Buffer Buffer;

        typedef std::function<void(const std::vector<Device> &)> DevicesChangedCallback;
        typedef std::function<void(Buffer)> NewBufferCallback;

        virtual DeviceList &devices() = 0;
        virtual void start(const Device &device, NewBufferCallback callback) = 0;
        virtual void stop() = 0;

    private:

    };
}

#endif //SPECTROGRAM_BACKEND_H
