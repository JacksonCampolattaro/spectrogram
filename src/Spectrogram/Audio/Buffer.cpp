//
// Created by jackcamp on 9/29/20.
//

#include "Buffer.h"

size_t Spectrogram::Audio::Buffer::numFrames() const {
    return channels[0].size();
}
