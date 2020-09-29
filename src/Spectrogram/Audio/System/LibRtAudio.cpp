//
// Created by jackcamp on 9/29/20.
//

#include "LibRtAudio.h"

void Spectrogram::Audio::System::LibRtAudio::setBufferSize(size_t size) {

    // TODO
}

Spectrogram::Audio::Buffer Spectrogram::Audio::System::LibRtAudio::getBuffer() {
    return Spectrogram::Audio::Buffer();
}

std::vector<Spectrogram::Audio::Device> Spectrogram::Audio::System::LibRtAudio::getDevices() {

    std::vector<Device> devices;

    for (size_t i = 0; i < _rtAudio.getDeviceCount(); ++i) {

        RtAudio::DeviceInfo deviceInfo = _rtAudio.getDeviceInfo(i);

        devices.emplace_back(deviceInfo.name, i, deviceInfo.isDefaultOutput || deviceInfo.isDefaultInput,
                             (bool) deviceInfo.inputChannels);
    }

    return devices;
}

void Spectrogram::Audio::System::LibRtAudio::setDevice(Spectrogram::Audio::Device &device) {

}
