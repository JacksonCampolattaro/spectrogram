//
// Created by jackcamp on 10/6/20.
//

#include "System.h"

Spectrogram::Audio::System::System::System(std::unique_ptr<Backend::Backend> backend) :
        _backend(std::move(backend)) {}

const Spectrogram::Audio::DeviceList &Spectrogram::Audio::System::System::devices() {
    return _backend->devices();
}

void Spectrogram::Audio::System::System::start(const Device &device) {
    _backend->stop();
    _backend->start(device,
                    [this](auto array) {
                        pushSamples(array);
                    });
}

void Spectrogram::Audio::System::System::stop() {
    _backend->stop();
}
