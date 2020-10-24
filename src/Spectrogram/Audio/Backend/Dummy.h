#ifndef SPECTROGRAM_DUMMY_H
#define SPECTROGRAM_DUMMY_H

#include <Spectrogram/Audio/Backend/Backend.h>
#include <thread>
#include <atomic>

namespace Spectrogram::Audio::Backend {

    /**
     * @brief A backend implementation designed for testing of code built on top of the backend
     */
    class Dummy : public Backend {

    public:

        /**
         * @brief Constructor which can be used to configure the generator
         * @param frequency the frequency (in Hz) of the output signal
         */
        Dummy(float frequency);

        DeviceList &devices() override;

        void start(const Device &device, size_t frames, NewSamplesCallback callback) override;

        void stop() override;

    private:

        DeviceList _devices;
        std::thread _t;
        std::atomic<bool> _stop;

        float _frequency;
        float _sampleRate = 48000;
        int _sampleNumber = 0;
    };

}


#endif //SPECTROGRAM_DUMMY_H
