//
// Created by jackcamp on 9/29/20.
//

#include "LibPulseAudio.h"

Spectrogram::Audio::System::LibPulseAudio::LibPulseAudio() {


    _pulseAudio = pa_simple_new(NULL, "spectrogram", PA_STREAM_RECORD,
                                NULL, "record", &_sampleSpec, NULL, NULL, NULL);
}

void Spectrogram::Audio::System::LibPulseAudio::setBufferSize(size_t size) {

}

Spectrogram::Audio::Buffer Spectrogram::Audio::System::LibPulseAudio::getBuffer() {
    return Spectrogram::Audio::Buffer();
}

std::vector<Spectrogram::Audio::Device> Spectrogram::Audio::System::LibPulseAudio::getDevices() {

    std::vector<Device> devices;

//    size_t defaultOutput = pa_();
//    size_t defaultInput = Pa_GetDefaultInputDevice();
//
//    for (size_t i = 0; i < Pa_GetDeviceCount(); ++i) {
//
//        auto deviceInfo = Pa_GetDeviceInfo(i);
//
//        if (deviceInfo->maxOutputChannels)
//            devices.emplace_back(deviceInfo->name, i, i == defaultInput || i == defaultOutput,
//                                 (bool) deviceInfo->maxInputChannels);
//    }

    return devices;
}

void Spectrogram::Audio::System::LibPulseAudio::setDevice(Spectrogram::Audio::Device &device) {

}
