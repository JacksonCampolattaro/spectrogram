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

                    size_t bufferSize = 100;

                    // Sleep for the amount of time it should take to fill a buffer this size
                    float bufferTime = bufferSize / _sampleRate;
                    std::this_thread::sleep_for(std::chrono::duration<float>(bufferTime));

                    // Fill left and right channels
                    Channel l;
                    Channel r;
                    for (int i = 0; i < bufferSize; ++i) {
                        _sampleNumber++;

                        // Calculate the time (in seconds) that this source has been running
                        float time = (float) _sampleNumber / (float) _sampleRate;

                        // Find the value of a sinusoid for this sample
                        Sample sinusoid = sin((float) time * _frequency * 2 * M_PI);

                        // If the user chose a sinusoid, add a sample using that equation
                        if (device.name == "Sinusoid") {

                            l.push_back(sinusoid);
                            r.push_back(sinusoid);
                        }

                        // If the user chose a Square wave, add a sample using that equation
                        if (device.name == "Square") {

                            l.push_back(sinusoid >= 0 ? 1.0 : -1.0);
                            r.push_back(sinusoid >= 0 ? 1.0 : -1.0);
                        }

                        // If the user chose a Sawtooth wave, add a sample using that equation
                        if (device.name == "Sawtooth") {

                            l.push_back(acos(sinusoid) / M_PI_2 - 1.0f);
                            r.push_back(acos(sinusoid) / M_PI_2 - 1.0f);
                        }
                    }

                    // Add both channels to the newly created buffer
                    Buffer b;
                    b.push_back(l);
                    b.push_back(r);

                    // Notify the system of the new buffer
                    callback(b);
                }
            }
    );
}

void Spectrogram::Audio::Backend::Dummy::stop() {

    _stop = true;
    _t.join();
}
