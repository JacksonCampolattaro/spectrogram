//
// Created by jackcamp on 9/29/20.
//

#include <assert.h>
#include "Buffer.h"

Spectrogram::Audio::Buffer::Buffer(const Spectrogram::Audio::Device &device, size_t numFrames) {

    _channels.resize(device.channelCount);
    for (auto &channel : _channels)
        channel.resize(numFrames);

    _timeLength = (float) numFrames / (float) device.sampleRate;
}

size_t Spectrogram::Audio::Buffer::numFrames() const {
    assert(numChannels() > 0);
    return _channels[0].size();
}

size_t Spectrogram::Audio::Buffer::numChannels() const {
    return _channels.size();
}

Spectrogram::Audio::FrameRange Spectrogram::Audio::Buffer::frames() {
    return FrameRange(*this);
}

Spectrogram::Audio::Buffer::ChannelRange &Spectrogram::Audio::Buffer::channels() {
    return _channels;
}

const Spectrogram::Audio::Buffer::ChannelRange &Spectrogram::Audio::Buffer::channels() const {
    return _channels;
}

float Spectrogram::Audio::Buffer::time() const {
    return _timeLength;
}

