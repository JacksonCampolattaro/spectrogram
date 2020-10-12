#ifndef SPECTROGRAM_SYSTEM_H
#define SPECTROGRAM_SYSTEM_H

#include <Spectrogram/Audio/Backend/Backend.h>

#include <memory>

namespace Spectrogram::Audio::System {

    class System {
    public:

        System(std::unique_ptr<Backend::Backend> backend);

        const DeviceList &devices();

        void start(const Device &device, size_t frames);

        void stop();

        virtual void pushSamples(std::vector<Sample *> arrays, size_t length) = 0;

    private:

        std::unique_ptr<Backend::Backend> _backend;
    };

}

#endif //SPECTROGRAM_SYSTEM_H
