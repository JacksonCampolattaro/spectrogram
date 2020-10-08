#ifndef SPECTROGRAM_DUMMY_H
#define SPECTROGRAM_DUMMY_H

#include <Spectrogram/Audio/Backend/Backend.h>
#include <thread>
#include <atomic>

namespace Spectrogram::Audio::Backend {

    class Dummy : public Backend {

    public:

        Dummy(float frequency);

        DeviceList &devices() override;

        void start(const Device &device, typename Backend::NewBufferCallback callback) override;

        void stop() override;

    private:

        DeviceList _devices;
        std::thread _t;
        std::atomic<bool> _stop;

        float _frequency;
        float _sampleRate = 1000;
        int _sampleNumber = 0;
    };

}


#endif //SPECTROGRAM_DUMMY_H
