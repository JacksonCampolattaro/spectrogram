//
// Created by jackcamp on 9/29/20.
//

#include "LibPortAudio.h"

Spectrogram::Audio::System::LibPortAudio::LibPortAudio() {

    Pa_Initialize();
}

void Spectrogram::Audio::System::LibPortAudio::setBufferSize(size_t size) {

}

Spectrogram::Audio::Buffer Spectrogram::Audio::System::LibPortAudio::getBuffer() {
    return Spectrogram::Audio::Buffer();
}

std::vector<Spectrogram::Audio::Device> Spectrogram::Audio::System::LibPortAudio::getDevices() {

    std::vector<Device> devices;

    size_t defaultOutput = Pa_GetDefaultOutputDevice();
    size_t defaultInput = Pa_GetDefaultInputDevice();

    for (size_t i = 0; i < Pa_GetDeviceCount(); ++i) {

        auto deviceInfo = Pa_GetDeviceInfo(i);

        if (deviceInfo->maxOutputChannels)
            devices.emplace_back(deviceInfo->name, i, i == defaultInput || i == defaultOutput,
                                 (bool) deviceInfo->maxInputChannels);
    }

    return devices;
}

void Spectrogram::Audio::System::LibPortAudio::setDevice(Spectrogram::Audio::Device &device) {

}
