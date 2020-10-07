#ifndef SPECTROGRAM_BUFFER_H
#define SPECTROGRAM_BUFFER_H

#include <vector>

namespace Spectrogram::Audio {
    typedef float Sample;
    typedef std::vector<Sample> Channel;
    typedef std::vector<Channel> Buffer;
}


#endif //SPECTROGRAM_BUFFER_H
