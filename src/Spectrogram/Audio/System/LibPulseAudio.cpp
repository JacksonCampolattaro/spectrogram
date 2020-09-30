//
// Created by jackcamp on 9/29/20.
//

#include "LibPulseAudio.h"

Spectrogram::Audio::System::LibPulseAudio::LibPulseAudio() {

}

void Spectrogram::Audio::System::LibPulseAudio::setBufferSize(size_t size) {

}

Spectrogram::Audio::Buffer Spectrogram::Audio::System::LibPulseAudio::getBuffer() {
    return Spectrogram::Audio::Buffer();
}

std::vector<Spectrogram::Audio::Device> Spectrogram::Audio::System::LibPulseAudio::getDevices() {
    return std::vector<Device>();
}

void Spectrogram::Audio::System::LibPulseAudio::setDevice(Spectrogram::Audio::Device &device) {

}
