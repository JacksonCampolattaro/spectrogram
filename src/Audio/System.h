#ifndef SPECTROGRAM_SYSTEM_H
#define SPECTROGRAM_SYSTEM_H

#include <rtaudio/RtAudio.h>

namespace Audio {

    class System {

    public:

        System() = default;

        RtAudio _rtAudio;

    };

}


#endif //SPECTROGRAM_SYSTEM_H
