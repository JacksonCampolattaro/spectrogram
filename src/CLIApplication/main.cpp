
//*
#include <Spectrogram/Audio/System/LibSoundio.h>

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

    for (;;) {
        for (auto sample : system.getBuffer()) {
            std::cout << sample << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
//*/

//#include <pulse/error.h>
//#include <pulse/pulseaudio.h>
//#include <pulse/simple.h>
//
//int main() {
//
//}
