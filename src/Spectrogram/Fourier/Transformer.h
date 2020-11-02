#ifndef SPECTROGRAM_TRANSFORMER_H
#define SPECTROGRAM_TRANSFORMER_H

#include <Spectrogram/Audio/Buffer.h>
#include <Spectrogram/Fourier/FrequencyDomainBuffer.h>
#include <Spectrogram/Fourier/processor.h>

namespace Spectrogram::Fourier {

    FrequencyDomainBuffer transform(const Audio::Buffer &buffer) {
        static Processor processor;

        std::vector<std::vector<Intensity>> intensities;
        for (const auto &channel : buffer.channels())
            intensities.push_back(processor.compute(channel));

        FrequencyDomainBuffer frequencyDomainBuffer;
        for (size_t index = 0; index < intensities.size(); ++index) {

            // FIXME: This is temporary
            Frequency frequency = index;

            frequencyDomainBuffer.emplace(std::make_pair(frequency, intensities[index]));

        }

        return frequencyDomainBuffer;
    }

}

#endif //SPECTROGRAM_TRANSFORMER_H
