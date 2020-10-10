//
// Created by jackcamp on 10/6/20.
//

#include "Blocking.h"


Spectrogram::Audio::System::Blocking::Blocking(std::unique_ptr<Backend::Backend> backend) :
        System(std::move(backend)) {

}

void Spectrogram::Audio::System::Blocking::newBufferHandler(Spectrogram::Audio::Buffer buffer) {

    // Add a buffer to the queue
    _bufferQueue.push(buffer);

    // Make sure the
    _bufferAdded.notify_one();
}

Spectrogram::Audio::Buffer Spectrogram::Audio::System::Blocking::getBuffer() {

    if (_bufferQueue.empty()) {

        std::mutex m;
        std::unique_lock<std::mutex> lock(m);
        _bufferAdded.wait(lock, [=] { return !_bufferQueue.empty(); });
    }

    // Consume the next buffer from the queue
    auto buffer = _bufferQueue.front();
    _bufferQueue.pop();
    return buffer;
}
