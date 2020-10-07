#include "Dummy.h"

Spectrogram::Audio::DeviceList &Spectrogram::Audio::Backend::Dummy::devices() {
    return _devices;
}

void Spectrogram::Audio::Backend::Dummy::start(const Spectrogram::Audio::Device &device,
                                               Spectrogram::Audio::Backend::Backend::NewBufferCallback callback) {

    for (;;) {

        Buffer b;
        for (int i = 0; i < 100; ++i) {
            b.push_back(i % 2);
        }
        callback(b);
    }
}

void Spectrogram::Audio::Backend::Dummy::stop() {

}
