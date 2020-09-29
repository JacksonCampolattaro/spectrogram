#include <cassert>
#include "LibSoundio.h"

Spectrogram::Audio::System::LibSoundio::LibSoundio() {

    _soundio = soundio_create();
    soundio_connect(_soundio);
    soundio_flush_events(_soundio);
}

Spectrogram::Audio::System::LibSoundio::~LibSoundio() {

    soundio_destroy(_soundio);
}

void Spectrogram::Audio::System::LibSoundio::setBufferSize(size_t size) {

}

Spectrogram::Audio::Buffer Spectrogram::Audio::System::LibSoundio::getBuffer() {
    return Spectrogram::Audio::Buffer();
}

std::vector<Spectrogram::Audio::Device> Spectrogram::Audio::System::LibSoundio::getDevices() {

    std::vector<Device> devices;

    size_t defaultDevice = soundio_default_output_device_index(_soundio);

    for (size_t i = 0; i < soundio_output_device_count(_soundio); ++i) {

        auto deviceInfo = soundio_get_output_device(_soundio, i);

        devices.emplace_back(deviceInfo->name, i, i == defaultDevice);
    }

    return devices;
}

void Spectrogram::Audio::System::LibSoundio::setDevice(Spectrogram::Audio::Device &device) {

    auto soundio_device = soundio_get_input_device(_soundio, device.id);
    assert(!soundio_device->probe_error);
}
