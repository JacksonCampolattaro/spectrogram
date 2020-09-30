
#include <Spectrogram/Audio/System/LibSoundio.h>

#include <iostream>
#include <memory>

using namespace Spectrogram::Audio;

int main() {

    // Initialize the system
    std::shared_ptr<System::System> system = std::make_shared<System::LibSoundio>();

    // List the devices
    std::cout << "Devices:" << std::endl;
    for (auto device : system->getDevices())
        std::cout << device << std::endl;

    system->setDevice(system->getDevices()[2]);


    for (;;) {

        system->getBuffer();
    }

    return EXIT_SUCCESS;
}
