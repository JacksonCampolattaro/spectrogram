
#include <Spectrogram/Audio/System/Blocking.h>
#include <Spectrogram/Audio/Backend/Soundio.h>

#include <iostream>
#include <memory>

using namespace Spectrogram::Audio;

int main() {

    // Initialize the system
    auto system = System::Blocking(std::make_unique<Backend::Soundio>());

    // List the devices
    std::cout << "Devices:" << std::endl;
    for (const auto &device : system.devices())
        std::cout << device << std::endl;

    int device = 2;
    std::cout << "\nInput device" << std::endl;
    std::cout << system.devices()[device] << std::endl;
    system.start(system.devices()[device]);

    for (int i = 0; i < 100; ++i) {

        for (auto sample : system.getBuffer()) {
            std::cout << sample << std::endl;
        }
    }

    system.stop();

    return EXIT_SUCCESS;
}
