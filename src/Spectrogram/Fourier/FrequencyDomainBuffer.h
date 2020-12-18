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
            assert(upper > lower);
            assert(upper <= maxFrequency());

            Audio::Frame frame;
            frame.resize(at(0).size());

            // TODO: I hate this **even more**

            int n = 10;
            double value = lower;
            for (int i = 0; i < n; ++i) {
                auto f = at(value);
                for (size_t j = 0; j < f.size(); ++j) {
                    frame[j] += f[j] / (float) n;
                }
                value += (upper - lower) / n;
            }

            return frame;
        }

        [[nodiscard]] float maxFrequency() const {
            return numFrames() / time();
        }
    };
}

#endif //SPECTROGRAM_FREQUENCYDOMAINBUFFER_H
