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

                    Channel l;
                    for (int i = 0; i < 100; ++i) {
                        l.push_back(i % 2);
                    }

                    Channel r;
                    for (int i = 0; i < 100; ++i) {
                        r.push_back(i % 2);
                    }

                    Buffer b;
                    b.push_back(l);
                    b.push_back(r);

                    callback(b);
                }
            }
    );
}

void Spectrogram::Audio::Backend::Dummy::stop() {

    _stop = true;
    _t.join();
}
