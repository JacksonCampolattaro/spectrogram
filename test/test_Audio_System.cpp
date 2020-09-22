
#include <catch2/catch.hpp>

#include <Audio/System.h>

TEST_CASE("Connecting to system audio", "[Audio::System]") {

    Audio::System system;

    std::cout << system._rtAudio.getDeviceCount() << " Devices" << std::endl;
}

TEST_CASE("Printing out all devices", "[Audio::System]") {

    Audio::System system;

    for (auto deviceName : system.devices())
        std::cout << deviceName << std::endl;
}
