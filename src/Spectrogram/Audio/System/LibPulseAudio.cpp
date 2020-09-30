//
// Created by jackcamp on 9/29/20.
//

#include "LibPulseAudio.h"

Spectrogram::Audio::System::LibPulseAudio::LibPulseAudio() {


//    _pulseAudio = pa_simple_new(NULL, "spectrogram", PA_STREAM_RECORD,
//                                NULL, "record", &_sampleSpec, NULL, NULL, NULL);
}

void Spectrogram::Audio::System::LibPulseAudio::setBufferSize(size_t size) {

}

Spectrogram::Audio::Buffer Spectrogram::Audio::System::LibPulseAudio::getBuffer() {

    static const pa_sample_spec sampleSpec = {.format = PA_SAMPLE_S16BE, .rate = 44100, .channels = 2};

    const int frames = 10000;
    const int fragmentSize = frames * sampleSpec.channels * sampleSpec.format;
    pa_buffer_attr buffer = {.maxlength = (uint32_t)-1, .fragsize = fragmentSize};

    _pulseAudio = pa_simple_new(nullptr, "spectrogram",
                                PA_STREAM_RECORD, nullptr, "record",
                                &sampleSpec, nullptr, &buffer, nullptr);

    int16_t data[frames * sampleSpec.channels];

    while (_pulseAudio) {

        int err = 0;
        pa_simple_read(_pulseAudio, data, sizeof(data), &err);

        for (int frame = 0; frame < frames; ++frame) {
            for (int channel = 0; channel < sampleSpec.channels; ++channel) {
                std::cout << data[(frame * sampleSpec.channels) + channel] << "\t";
            }
            std::cout << "\n";
        }
        std::cout << "\n" << std::endl;
    }

    pa_simple_free(_pulseAudio);

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
