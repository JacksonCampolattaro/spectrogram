//
// Created by jackcamp on 9/29/20.
//

#include <assert.h>
#include "Buffer.h"

size_t Spectrogram::Audio::Buffer::numFrames() const {
    assert(numChannels() > 0);
    return channels[0].size();
}

size_t Spectrogram::Audio::Buffer::numChannels() const {
    return channels.size();
}

Spectrogram::Audio::FrameRange Spectrogram::Audio::Buffer::frames() {
    return FrameRange(*this);
}

