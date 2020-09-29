#ifndef SPECTROGRAM_SYSTEM_H
#define SPECTROGRAM_SYSTEM_H

#include <Spectrogram/Audio/RtAudio.h>

namespace Audio {

    class System {

    public:

        System() = default;

        void devices() {
            // TODO: What should the return type be?

            for (int i = 0; i < _rtAudio.getDeviceCount(); ++i) {

                std::cout << i << " " << _rtAudio.getDeviceInfo(i) << std::endl;
            }

        }

        RtAudio _rtAudio;

    };

}


#endif //SPECTROGRAM_SYSTEM_H
