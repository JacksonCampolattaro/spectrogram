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

                        float time = (float) _sampleNumber / (float) _sampleRate;

                        if (device.name == "Sinusoid") {

                            l.push_back(sin((float) time * _frequency * 2 * M_PI));
                            r.push_back(sin((float) time * _frequency * 2 * M_PI));
                        }

                        if (device.name == "Square") {

                            l.push_back(
                                    sin((float) time * _frequency * 2 * M_PI) >= 0 ? 1.0 : -1.0
                                    );
                            r.push_back(
                                    sin((float) time * _frequency * 2 * M_PI) >= 0 ? 1.0 : -1.0
                            );
                        }

                        if (device.name == "Sawtooth") {

                            l.push_back(
                                    acos(sin((float) time * _frequency * 2 * M_PI)) / M_PI_2 - 1.0f
                            );
                            r.push_back(
                                    acos(sin((float) time * _frequency * 2 * M_PI)) / M_PI_2 - 1.0f
                            );
                        }
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
