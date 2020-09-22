#ifndef SPECTROGRAM_SYSTEM_H
#define SPECTROGRAM_SYSTEM_H

#include <rtaudio/RtAudio.h>

namespace Audio {

    class System {

    public:

        System() = default;

        std::vector<std::string> devices() {

            std::vector<std::string> d;

            for (int i = 0; i < _rtAudio.getDeviceCount(); ++i) {
                d.emplace_back(_rtAudio.getDeviceInfo(i).name);
            }

            return d;
        }

        RtAudio _rtAudio;

    };

}


#endif //SPECTROGRAM_SYSTEM_H
