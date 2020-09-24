#ifndef SPECTROGRAM_RTAUDIO_H
#define SPECTROGRAM_RTAUDIO_H

#include <rtaudio/RtAudio.h>

#include <iostream>

std::ostream &operator<<(std::ostream &os, const RtAudio::DeviceInfo &deviceInfo) {

    os << "device:" << std::endl;
    os << "\tname: \"" << deviceInfo.name << "\"" << std::endl;
    os << "\toutput: " << deviceInfo.outputChannels << " channels" << std::endl;
    os << "\tinput: " << deviceInfo.inputChannels << " channels" << std::endl;
    os << "\tduplex: " << deviceInfo.duplexChannels << " channels" << std::endl;

    os << "\tsample rates: [ ";
    for (auto rate : deviceInfo.sampleRates)
        os << rate << " ";
    os << "]" << std::endl;

    os << "\tpreferred rate: " << deviceInfo.preferredSampleRate << std::endl;


    if (deviceInfo.isDefaultInput)
        os << "\t(default input)" << std::endl;

    if (deviceInfo.isDefaultOutput)
        os << "\t(default output)" << std::endl;

    return os;
}


#endif //SPECTROGRAM_RTAUDIO_H
