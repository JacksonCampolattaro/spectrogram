#ifndef SPECTROGRAM_CALLBACK_H
#define SPECTROGRAM_CALLBACK_H

#include <Spectrogram/Audio/Backend/Backend.h>
#include <memory>

namespace Spectrogram::Audio::System {

    class Callback {
    public:

        Callback(std::unique_ptr<Backend::Backend> backend);

        const DeviceList &devices();

        void start(Device &device);

        void stop();

        virtual void newBufferHandler(Buffer buffer);

    private:

        std::unique_ptr<Backend::Backend> _backend;
    };

}


#endif //SPECTROGRAM_CALLBACK_H
