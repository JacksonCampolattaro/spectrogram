#include "Dummy.h"

#include <math.h>

Spectrogram::Audio::Backend::Dummy::Dummy(float frequency) : _frequency(frequency) {
    _devices.emplace_back("Sinusoid", 0, true);
    _devices.emplace_back("Square", 1, false);
    _devices.emplace_back("Sawtooth", 2, false);
}

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
                    Channel r;
                    for (int i = 0; i < 100; ++i) {
                        _sampleNumber++;

                        l.push_back(sin((float) _sampleNumber * _frequency / _sampleRate));
                        r.push_back(sin((float) _sampleNumber * _frequency / _sampleRate));
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
