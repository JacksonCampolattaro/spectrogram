#include "Event.h"

Spectrogram::Audio::System::Event::Event(std::unique_ptr<Backend::Backend> backend) :
        System(std::move(backend)) {
}

void Spectrogram::Audio::System::Event::start(const Spectrogram::Audio::Device &device,
                                              std::chrono::milliseconds maxLatency, size_t bufferLength) {

    // Prepare the channel queues
    for (size_t channel = 0; channel < device.channelCount; ++channel) {
        _channelQueues.emplace_back(device.sampleRate * maxLatency.count() / 1000);
    }

    // Prepare the buffer
    _buffer.resize(device.channelCount);
    for (auto &channel : _buffer) {
        channel.resize(bufferLength);
    }

    // Start the backend
    System::start(device);
}

void Spectrogram::Audio::System::Event::pushSamples(const std::vector<Sample *> &arrays, size_t length) {


    for (size_t channel = 0; channel < _channelQueues.size(); ++channel) {
        [[maybe_unused]] auto samplesPushed = _channelQueues[channel].push(arrays[channel], length);
        assert(samplesPushed == length);
    }

    newDataNotification();
}
