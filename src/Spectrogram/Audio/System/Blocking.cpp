//
// Created by jackcamp on 10/6/20.
//

#include "Blocking.h"


Spectrogram::Audio::System::Blocking::Blocking(std::unique_ptr<Backend::Backend> backend) :
        System(std::move(backend)) {

}

void Spectrogram::Audio::System::Blocking::start(const Spectrogram::Audio::Device &device, size_t frames) {

    for (int channel = 0; channel < device.channelCount; ++channel) {
        _channelQueues.emplace_back(2000);
    }
    _frames = frames;
    System::start(device, frames);
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

    Spectrogram::Audio::Buffer buffer;
    buffer.resize(_channelQueues.size());

    for (size_t frame = 0; frame < _frames; ++frame) {
        for (size_t channel = 0; channel < buffer.size(); ++channel) {

            while (_channelQueues[channel].read_available() < _frames) {}

            buffer[channel].push_back(_channelQueues[channel].front());
            _channelQueues[channel].pop();
        }
    }
    assert(buffer.size() == 2);
    return buffer;
}

void Spectrogram::Audio::System::Blocking::pushSamples(const std::vector<Sample *> &arrays, size_t length) {

//
//    // Add a buffer to the queue
//    auto success = _bufferQueue.push(buffer);
//    assert(success);
//
//    // Make sure the consuming end is notified
//    _bufferAdded.notify_one();

    for (int channel = 0; channel < _channelQueues.size(); ++channel) {
        _channelQueues[channel].push(arrays[channel], length);
    }
}
