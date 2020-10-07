
#include <catch2/catch.hpp>

#include <Spectrogram/Audio/System/System.h>
#include <Spectrogram/Audio/System/Blocking.h>

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


TEST_CASE("Dummy devices", "[Dummy]") {

    auto system = System::Blocking(std::make_unique<Backend::Dummy>());

    Device d{"test", 0, false};
    system.start(d);

    auto b = system.getBuffer();
    for (int sample = 0; sample < b[0].size(); ++sample) {
        for (int channel = 0; channel < b.size(); ++channel) {
            std::cout << b[channel][sample] << " ";
        }
    }
    std::cout << std::endl;

    system.stop();
}
