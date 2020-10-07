//
// Created by jackcamp on 10/6/20.
//

#include "Callback.h"

using namespace std::placeholders;

Spectrogram::Audio::System::Callback::Callback(std::unique_ptr<Backend::Backend> backend) :
        _backend(std::move(backend)) {}

const Spectrogram::Audio::DeviceList &Spectrogram::Audio::System::Callback::devices() {
    return _backend->devices();
}

void Spectrogram::Audio::System::Callback::start(Spectrogram::Audio::Device &device) {
    _backend->start(device, std::bind(&Callback::newBufferHandler, this, _1));
}

void Spectrogram::Audio::System::Callback::stop() {

}

void Spectrogram::Audio::System::Callback::newBufferHandler(Spectrogram::Audio::Buffer buffer) {

    for (auto sample : buffer) {
        std::cout << sample << std::endl;
    }
}
