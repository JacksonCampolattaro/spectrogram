#include "Dummy.h"

Spectrogram::Audio::DeviceList &Spectrogram::Audio::Backend::Dummy::devices() {
    return _devices;
}

void Spectrogram::Audio::Backend::Dummy::start(const Spectrogram::Audio::Device &device,
                                               Spectrogram::Audio::Backend::Backend::NewBufferCallback callback) {

    _stop = false;

    _t = std::thread(
            [=] {

                while (!_stop) {

                    Buffer b;
                    b.reserve(1);
                    for (int i = 0; i < 100; ++i) {
                        b[0].push_back(i % 2);
                    }
                    callback(b);
                }
            }
    );
}

void Spectrogram::Audio::Backend::Dummy::stop() {

    _stop = true;
    _t.join();
}
