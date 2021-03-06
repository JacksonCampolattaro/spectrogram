//
// Created by jackcamp on 10/6/20.
//

#include "Blocking.h"


Spectrogram::Audio::System::Blocking::Blocking(std::unique_ptr<Backend::Backend> backend) :
        System(std::move(backend)) {

}

void Spectrogram::Audio::System::Blocking::start(const Spectrogram::Audio::Device &device,
                                            std::chrono::milliseconds maxLatency) {

    for (size_t channel = 0; channel < device.channelCount; ++channel) {
        _channelQueues.emplace_back(device.sampleRate * maxLatency.count() / 1000);
    }
    System::start(device);
}

void Spectrogram::Audio::System::Blocking::fillBuffer(Spectrogram::Audio::Buffer &buffer) {

    // Wait for enough elements to be available
    if (_channelQueues[0].read_available() < buffer.numFrames()) {

        std::mutex m;
        std::unique_lock<std::mutex> lock(m);
        _samplesAdded.wait(lock, [=] { return _channelQueues[0].read_available() >= buffer.numFrames(); });
    }

    // Fill up the buffer
    for (size_t frame = 0; frame < buffer.numFrames(); ++frame) {
        for (size_t channel = 0; channel < buffer.numChannels(); ++channel) {

            buffer.channels()[channel][frame] = _channelQueues[channel].front();
            _channelQueues[channel].pop();
        }
    }
}

void Spectrogram::Audio::System::Blocking::pushSamples(const std::vector<Sample> *array) {

    if (array) {

        for (size_t channel = 0; channel < _channelQueues.size(); ++channel) {
            _channelQueues[channel].push((*array)[channel]);
        }

    } else {

        _samplesAdded.notify_one();
    }
}
