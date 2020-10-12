//
// Created by jackcamp on 10/6/20.
//

#include "Blocking.h"


Spectrogram::Audio::System::Blocking::Blocking(std::unique_ptr<Backend::Backend> backend) :
        System(std::move(backend)) {

}

Spectrogram::Audio::Buffer Spectrogram::Audio::System::Blocking::getBuffer() {

//    if (_bufferQueue.empty()) {
//
//        std::mutex m;
//        std::unique_lock<std::mutex> lock(m);
//        _bufferAdded.wait(lock, [=] { return !_bufferQueue.empty(); });
//    }
//
//    // Consume the next buffer from the queue
//    auto buffer = _bufferQueue.front();
//    _bufferQueue.pop();
//    return buffer;
}

void Spectrogram::Audio::System::Blocking::pushSamples(std::vector<Sample *> arrays, size_t length) {

//
//    // Add a buffer to the queue
//    auto success = _bufferQueue.push(buffer);
//    assert(success);
//
//    // Make sure the consuming end is notified
//    _bufferAdded.notify_one();
}
