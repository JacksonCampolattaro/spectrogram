
#include <Spectrogram/Audio/System/LibSoundio.h>

#include <iostream>

using namespace Spectrogram::Audio;

int main() {

    System::LibSoundio system{};

    std::cout << "Devices:" << std::endl;
    for (auto device : system.getDevices())
        std::cout << device << std::endl;

    return EXIT_SUCCESS;
}
