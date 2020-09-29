
#include <Spectrogram/Audio/System/LibSoundio.h>

#include <iostream>
#include <memory>

using namespace Spectrogram::Audio;

int main() {

    // Initialize the system
    std::shared_ptr<System::System> system = std::make_shared<System::LibSoundio>();

    std::cout << "Devices:" << std::endl;
    for (auto device : system->getDevices())
        std::cout << device << std::endl;

    for (;;) {

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
