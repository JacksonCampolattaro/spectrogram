//
// Created by jackcamp on 10/6/20.
//

#include "Callback.h"

Spectrogram::Audio::System::Callback::Callback(std::unique_ptr<Backend::Backend> backend) :
        _backend(std::move(backend)) {}

const Spectrogram::Audio::DeviceList &Spectrogram::Audio::System::Callback::devices() {
    return _backend->devices();
}

void Spectrogram::Audio::System::Callback::start(const Spectrogram::Audio::Device &device) {
    _backend->start(device,
                    [this](auto buffer) {
                        newBufferHandler(buffer);
                    }
    );
}

void Spectrogram::Audio::System::Callback::stop() {
    _backend->stop();
}

void Spectrogram::Audio::System::Callback::newBufferHandler(Spectrogram::Audio::Buffer buffer) {

    for (auto sample : buffer) {
        std::cout << sample << std::endl;
    }
}
