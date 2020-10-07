//
// Created by jackcamp on 10/6/20.
//

#include "Blocking.h"


Spectrogram::Audio::System::Blocking::Blocking(std::unique_ptr<Backend::Backend> backend) :
        Callback(std::move(backend)) {

}

void Spectrogram::Audio::System::Blocking::newBufferHandler(Spectrogram::Audio::Buffer buffer) {

    {
        std::unique_lock<std::mutex> lock(_bufferQueueMutex);
        _bufferQueue.push(buffer);
    }
    _newBufferCondition.notify_one();
}

Spectrogram::Audio::Buffer Spectrogram::Audio::System::Blocking::getBuffer() {

    std::unique_lock<std::mutex> lock(_bufferQueueMutex);
    _newBufferCondition.wait(lock,
                             [=] {
                                 return !_bufferQueue.empty();
                             }
    );

    auto b = _bufferQueue.front();
    _bufferQueue.pop();
    return b;
}
