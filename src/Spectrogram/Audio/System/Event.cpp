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
    _buffer = std::make_unique<Buffer>(device, bufferLength);

    // Start the backend
    System::start(device);
}

void Spectrogram::Audio::System::Event::pushSamples(const std::vector<Sample> *array) {

    if (array) {

        for (size_t channel = 0; channel < _channelQueues.size(); ++channel) {
            _channelQueues[channel].push((*array)[channel]);
        }

    } else {

        notifyNewData();
    }

}

void Spectrogram::Audio::System::Event::checkForNewData() {

    // Data is available when the queues contain enough samples to fill the buffer
    if (_channelQueues[0].read_available() > _buffer->numFrames() / 2) {

        // Shift the existing data over
        size_t sampleNumber = 0;
        for (; sampleNumber < _buffer->numFrames() / 2; ++sampleNumber) {

            for (size_t channelNumber = 0; channelNumber < _buffer->numChannels(); ++channelNumber) {
                _buffer->channels()[channelNumber][sampleNumber]
                        = _buffer->channels()[channelNumber][sampleNumber + _buffer->numFrames() / 2];
            }
        }

        // Fill the buffer with new data
        for (; sampleNumber < _buffer->numFrames(); ++sampleNumber) {
            for (size_t channelNumber = 0; channelNumber < _buffer->numChannels(); ++channelNumber) {

                _buffer->channels()[channelNumber][sampleNumber] = _channelQueues[channelNumber].front();
                _channelQueues[channelNumber].pop();
            }
        }

        // Process the data
        processNewData(*_buffer);
    }
}
