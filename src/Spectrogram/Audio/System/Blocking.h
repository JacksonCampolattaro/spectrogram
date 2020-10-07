//
// Created by jackcamp on 10/6/20.
//

#ifndef SPECTROGRAM_BLOCKING_H
#define SPECTROGRAM_BLOCKING_H

#include <Spectrogram/Audio/System/System.h>

#include <queue>
#include <mutex>
#include <condition_variable>

namespace Spectrogram::Audio::System {

    class Blocking : public System {
    public:

        Blocking(std::unique_ptr<Backend::Backend> backend);

        void newBufferHandler(Buffer buffer) override;

        Buffer getBuffer();

    private:

        std::queue<Buffer> _bufferQueue;
        std::mutex _bufferQueueMutex;
        std::condition_variable _newBufferCondition;

    };
}


#endif //SPECTROGRAM_BLOCKING_H
