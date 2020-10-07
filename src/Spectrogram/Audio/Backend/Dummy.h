#ifndef SPECTROGRAM_DUMMY_H
#define SPECTROGRAM_DUMMY_H

#include <Spectrogram/Audio/Backend/Backend.h>

namespace Spectrogram::Audio::Backend {

    class Dummy : public Backend {

    public:

        Dummy() = default;

        DeviceList &devices() override {
            return _devices;
        }

        void start(const Device &device, typename Backend::NewBufferCallback callback) override {

        }

        void stop() override {

        }

    private:

        DeviceList _devices;
    };

}


#endif //SPECTROGRAM_DUMMY_H
