//
// Created by jackcamp on 10/18/20.
//

#include "Event.h"

Spectrogram::Audio::System::Event::Event(std::unique_ptr<Backend::Backend> backend) :
        System(std::move(backend)) {
}

void Spectrogram::Audio::System::Event::fillBuffer(Spectrogram::Audio::Buffer &buffer) {

    // Wait for enough elements to be available
    if (_channelQueues[0].read_available() < buffer[0].size()) {

        std::mutex m;
        std::unique_lock<std::mutex> lock(m);
        _samplesAdded.wait(lock, [=] { return _channelQueues[0].read_available() >= buffer[0].size(); });
    }

    // Fill up the buffer
    for (size_t frame = 0; frame < buffer[0].size(); ++frame) {
        for (size_t channel = 0; channel < buffer.size(); ++channel) {

            buffer[channel][frame] = _channelQueues[channel].front();
            _channelQueues[channel].pop();
        }
    }
}

void Spectrogram::Audio::System::Event::start(const Spectrogram::Audio::Device &device,
                                              std::chrono::milliseconds maxLatency) {

    for (size_t channel = 0; channel < device.channelCount; ++channel) {
        _channelQueues.emplace_back(device.sampleRate * maxLatency.count() / 1000);
    }
    System::start(device);
}

void Spectrogram::Audio::System::Event::pushSamples(const std::vector<Sample *> &arrays, size_t length) {


    for (size_t channel = 0; channel < _channelQueues.size(); ++channel) {
        [[maybe_unused]] auto samplesPushed = _channelQueues[channel].push(arrays[channel], length);
        assert(samplesPushed == length);
    }

    _samplesAdded.notify_one();
}