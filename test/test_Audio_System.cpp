
#include <catch2/catch.hpp>

#include <portaudio.h>

#include <Spectrogram/Audio/System/System.h>
#include <Spectrogram/Audio/System/LibRtAudio.h>
#include <Spectrogram/Audio/System/LibSoundio.h>
#include <Spectrogram/Audio/System/LibPortAudio.h>

#include <iostream>

using namespace Spectrogram::Audio;

TEST_CASE("Connecting to system audio", "[Audio::System]") {
//
//    Audio::System system;
//
//    std::cout << system._rtAudio.getDeviceCount() << " Devices" << std::endl;
}

TEST_CASE("RtAudio", "[Spectrogram::Audio::System::RtAudio]") {

    std::cout << "\nRtaudio"
                 "\n~~~~~~~" << std::endl;

    System::LibRtAudio system{};

    for (auto device : system.getDevices()) {

        std::cout << device.name
                << (device.defaultOutput ? " *" : "")
                << std::endl;
    }


}

TEST_CASE("LibSoundio", "[Spectrogram::Audio::System::LibSoundio]") {

    std::cout << "\nLibsoundio"
                 "\n~~~~~~~~~~" << std::endl;

    System::LibSoundio system{};

    for (auto device : system.getDevices()) {

        std::cout << device.name
                  << (device.defaultOutput ? " *" : "")
                  << std::endl;
    }

}

TEST_CASE("PortAudio", "[Spectrogram::Audio::System::PortAudio]") {

    std::cout << "\nPortAudio"
                 "\n~~~~~~~~~" << std::endl;

    System::LibPortAudio system{};

    for (auto device : system.getDevices()) {

        std::cout << device.name
                  << (device.defaultOutput ? " *" : "")
                  << std::endl;
    }

}
