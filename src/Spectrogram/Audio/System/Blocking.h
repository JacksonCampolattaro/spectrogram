//
// Created by jackcamp on 10/6/20.
//

#ifndef SPECTROGRAM_BLOCKING_H
#define SPECTROGRAM_BLOCKING_H

#include <Spectrogram/Audio/System/Callback.h>

namespace Spectrogram::Audio::System {

    class Blocking : public Callback {
    public:

        Blocking(std::unique_ptr<Backend::Backend> backend);

        void newBufferHandler(Buffer buffer) override;

        Buffer getBuffer();

    };
}


#endif //SPECTROGRAM_BLOCKING_H
