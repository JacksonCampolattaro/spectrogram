//
// Created by jackcamp on 10/6/20.
//

#include "System.h"

Spectrogram::Audio::System::System::System(std::unique_ptr<Backend::Backend> backend) :
        _backend(std::move(backend)) {}

const Spectrogram::Audio::DeviceList &Spectrogram::Audio::System::System::devices() {
    return _backend->devices();
}

void Spectrogram::Audio::System::System::start(const Device &device, size_t frames) {
    _backend->start(device, frames,
                    [this](auto arrays, auto length) {
                        pushSamples(arrays, length);
                    });
}

void Spectrogram::Audio::System::System::stop() {
    _backend->stop();
}
