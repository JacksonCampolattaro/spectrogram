#ifndef SPECTROGRAM_FREQUENCYDOMAINBUFFER_H
#define SPECTROGRAM_FREQUENCYDOMAINBUFFER_H

#include <map>
#include <vector>

namespace Spectrogram::Fourier {

    typedef float Intensity;

    typedef float Frequency;

    typedef std::map<Frequency, std::vector<Intensity>> FrequencyDomainBuffer;
}

#endif //SPECTROGRAM_FREQUENCYDOMAINBUFFER_H
