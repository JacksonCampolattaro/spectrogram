
//*
#include <Spectrogram/Audio/System/LibSoundio.h>

#include <iostream>
#include <memory>

using namespace Spectrogram::Audio;

int main() {

    // Initialize the system
    std::shared_ptr<System::System> system = std::make_shared<System::LibSoundio>();

    // List the devices
    std::cout << "Devices:" << std::endl;
    for (const auto &device : system->getDevices())
        std::cout << device << std::endl;

    int device = 2;
    std::cout << "\nInput device" << std::endl;
    std::cout << system->getDevices()[device] << std::endl;
    system->setDevice(system->getDevices()[device]);

    for (;;)
        system->getBuffer();

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
