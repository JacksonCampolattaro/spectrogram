//
// Created by jackcamp on 10/6/20.
//

#include "Blocking.h"


Spectrogram::Audio::System::Blocking::Blocking(std::unique_ptr<Backend::Backend> backend) :
        Callback(std::move(backend)) {

}

void Spectrogram::Audio::System::Blocking::newBufferHandler(Spectrogram::Audio::Buffer buffer) {

    for (auto sample : buffer) {
        std::cout << "x" << sample << std::endl;
    }
}

Spectrogram::Audio::Buffer Spectrogram::Audio::System::Blocking::getBuffer() {
    return Spectrogram::Audio::Buffer();
}
