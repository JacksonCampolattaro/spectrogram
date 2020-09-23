#ifndef SPECTROGRAM_RTAUDIO_H
#define SPECTROGRAM_RTAUDIO_H

#include <rtaudio/RtAudio.h>

#include <iostream>

std::ostream &operator<<(std::ostream &os, const RtAudio::DeviceInfo &deviceInfo) {

    std::cout << "device" << std::endl;
}


#endif //SPECTROGRAM_RTAUDIO_H
