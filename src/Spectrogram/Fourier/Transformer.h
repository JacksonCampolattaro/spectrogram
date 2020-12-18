#ifndef SPECTROGRAM_TRANSFORMER_H
#define SPECTROGRAM_TRANSFORMER_H

#include <Spectrogram/Audio/Buffer.h>
#include <Spectrogram/Fourier/FrequencyDomainBuffer.h>
#include <Spectrogram/Fourier/processor.h>

namespace Spectrogram::Fourier {

    FrequencyDomainBuffer transform(const Audio::Buffer &buffer) {
        static Processor processor;
        if ((size_t)processor.getSampleSize() != buffer.numFrames()) processor.setSampleSize(buffer.numFrames());

        FrequencyDomainBuffer frequencyDomainBuffer(buffer.time());
        for (const auto &channel : buffer.channels())
            frequencyDomainBuffer.channels().push_back(processor.compute(channel));

        for (auto &channel : frequencyDomainBuffer.channels())
            for (auto &sample : channel)
                sample = (sample + 90.0) / 90.0;

        return frequencyDomainBuffer;
    }

}

#endif //SPECTROGRAM_TRANSFORMER_H
