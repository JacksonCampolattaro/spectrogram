
#include <catch2/catch.hpp>

#include <Spectrogram/Audio/System/System.h>
#include <Spectrogram/Audio/System/LibSoundio.h>

#include <iostream>

using namespace Spectrogram::Audio;

TEST_CASE("Connecting to system audio", "[Audio::System]") {
//
//    Audio::System system;
//
//    std::cout << system._rtAudio.getDeviceCount() << " Devices" << std::endl;
}

TEST_CASE("LibSoundio", "[Spectrogram::Audio::System::LibSoundio]") {

    std::cout << "\nLibsoundio"
                 "\n~~~~~~~~~~" << std::endl;

    System::LibSoundio system{};

    for (auto device : system.getDevices()) {

        std::cout << device
                  << std::endl;
    }

}
