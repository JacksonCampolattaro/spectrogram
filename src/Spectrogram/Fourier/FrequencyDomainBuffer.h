#ifndef SPECTROGRAM_FREQUENCYDOMAINBUFFER_H
#define SPECTROGRAM_FREQUENCYDOMAINBUFFER_H

#include <Spectrogram/Audio/Buffer.h>

#include <map>
#include <vector>

namespace Spectrogram::Fourier {

    typedef float Intensity;

    typedef float Frequency;

    class FrequencyDomainBuffer : public Audio::Buffer {

    public:

        explicit FrequencyDomainBuffer(float time) {
            _timeLength = time;
        }

        [[nodiscard]] Audio::Frame at(double frequency) const {
            size_t index = frequency * time();

            Audio::Frame frame;
            for (const auto &channel : channels()) {
                frame.emplace_back(channel[index]);
            }

            return frame;
        }
    };
}

#endif //SPECTROGRAM_FREQUENCYDOMAINBUFFER_H
