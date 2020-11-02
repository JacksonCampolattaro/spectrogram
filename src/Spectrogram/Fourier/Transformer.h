#ifndef SPECTROGRAM_TRANSFORMER_H
#define SPECTROGRAM_TRANSFORMER_H

#include <Spectrogram/Audio/Buffer.h>
#include <Spectrogram/Fourier/FrequencyDomainBuffer.h>
#include <Spectrogram/Fourier/processor.h>

namespace Spectrogram::Fourier {

    FrequencyDomainBuffer transform(const Audio::Buffer &buffer) {
        static Processor processor;
        if ((size_t)processor.getSampleSize() != buffer.numFrames()) processor.setSampleSize(buffer.numFrames());

        std::vector<std::vector<Intensity>> intensities;
        for (const auto &channel : buffer.channels())
            intensities.push_back(processor.compute(channel));

        FrequencyDomainBuffer frequencyDomainBuffer;
        for (size_t index = 0; index < intensities[0].size(); ++index) {

            Frequency frequency = index / buffer.time();

            std::vector<Intensity> frame;
            for (auto channel : intensities)
                frame.push_back(channel[index]);

            frequencyDomainBuffer.emplace(std::make_pair(frequency, frame));

        }

        return frequencyDomainBuffer;
    }

}

#endif //SPECTROGRAM_TRANSFORMER_H
