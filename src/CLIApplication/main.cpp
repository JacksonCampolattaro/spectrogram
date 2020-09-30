
#include <Spectrogram/Audio/System/LibSoundio.h>

#include <iostream>
#include <memory>
#include <zconf.h>

using namespace Spectrogram::Audio;

int main() {

    // Initialize the system
    std::shared_ptr<System::System> system = std::make_shared<System::LibSoundio>();

    // List the devices
    std::cout << "Devices:" << std::endl;
    for (auto device : system->getDevices())
        std::cout << device << std::endl;

    system->setDevice(system->getDevices()[2]);

    system->getBuffer();

    for (;;) {

        sleep(0.01);
    }

    return EXIT_SUCCESS;
}
