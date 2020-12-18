#ifndef SPECTROGRAM_FREQUENCYDOMAINBUFFER_H
#define SPECTROGRAM_FREQUENCYDOMAINBUFFER_H

#include <Spectrogram/Audio/Buffer.h>

#include <map>
#include <vector>
#include <cmath>
#include <cassert>

namespace Spectrogram::Fourier {

    typedef float Intensity;

    typedef float Frequency;

    class FrequencyDomainBuffer : public Audio::Buffer {

    public:

        explicit FrequencyDomainBuffer(float time) {
            _timeLength = time;
        }

        [[nodiscard]] Audio::Frame at(double frequency) const {
            double index = frequency * time();

            Audio::Frame frame;
            for (const auto &channel : channels()) {

                // TODO: I hate _all_ of this

                if (floor(index) == index) {
                    frame.emplace_back(channel[index]);
                } else {

                    float belowIndex = floor(index);
                    float belowError = index - belowIndex;
                    float aboveIndex = ceil(index);
                    float aboveError = aboveIndex - index;

                    frame.emplace_back(
                            (channel[belowIndex] * (1 - belowError)) + (channel[aboveIndex] * (1 - aboveError))
                    );
                }

            }

            return frame;
        }

        [[nodiscard]] Audio::Frame at(double lower, double upper) const {
            assert(lower >= 0);
            assert(upper >= lower);
            assert(upper <= maxFrequency());

            double range = upper - lower;

//            size_t lowerIndex = lower * time();
//            size_t upperIndex = upper * time();

            if (range == 0) return at((lower + upper) / 2.0);

            Audio::Frame frame = at(lower);

            while (lower <= upper) {
                lower += 1.0f;

                auto f = at(lower);

                for (size_t i = 0; i < f.size(); ++i) {
                    frame[i] += f[i] / range;
                }

            }

//            for (const auto &channel : channels()) {
//
//                double value = 0;
//                for (size_t i = lowerIndex; i < upperIndex; ++i) {
//
//                    value += channel[i] / range;
//                }
//
//                frame.push_back(value);
//            }
//
            return frame;
        }

        [[nodiscard]] float maxFrequency() const {
            return numFrames() / time();
        }
    };
}

#endif //SPECTROGRAM_FREQUENCYDOMAINBUFFER_H
