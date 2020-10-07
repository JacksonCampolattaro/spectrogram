#ifndef SPECTROGRAM_DUMMY_H
#define SPECTROGRAM_DUMMY_H

#include <Spectrogram/Audio/Backend/Backend.h>
#include <thread>
#include <atomic>

namespace Spectrogram::Audio::Backend {

    class Dummy : public Backend {

    public:

        Dummy() = default;

        DeviceList &devices() override;

        void start(const Device &device, typename Backend::NewBufferCallback callback) override;

        void stop() override;

    private:

        DeviceList _devices;
        std::thread _t;
        std::atomic<bool> _stop;

    };

}


#endif //SPECTROGRAM_DUMMY_H
