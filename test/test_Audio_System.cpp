
#include <catch2/catch.hpp>

#include <Spectrogram/Audio/System/System.h>
#include <Spectrogram/Audio/System/Callback.h>
#include <Spectrogram/Audio/System/Blocking.h>
#include <Spectrogram/Audio/System/LibSoundio.h>

#include <Spectrogram/Audio/Backend/Dummy.h>

#include <iostream>
#include <unistd.h>

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

TEST_CASE("Dummy devices", "[Dummy]") {

    auto system = System::Blocking(std::make_unique<Backend::Dummy>());

    Device d{"test", 0, false};
    system.start(d);

    for (auto sample : system.getBuffer()) {
        std::cout << sample << " ";
    }
    std::cout << std::endl;

    system.stop();
}
