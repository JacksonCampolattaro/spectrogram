
#include <catch2/catch.hpp>

#include <portaudio.h>

#include <Spectrogram/Audio/System/System.h>
#include <Spectrogram/Audio/System/LibRtAudio.h>
#include <Spectrogram/Audio/System/LibSoundio.h>
#include <Spectrogram/Audio/System/LibPortAudio.h>
#include <Spectrogram/Audio/System/LibPulseAudio.h>

#include <iostream>

using namespace Spectrogram::Audio;

TEST_CASE("Connecting to system audio", "[Audio::System]") {
//
//    Audio::System system;
//
//    std::cout << system._rtAudio.getDeviceCount() << " Devices" << std::endl;
}

TEST_CASE("RtAudio", "[Spectrogram::Audio::System::LibRtAudio]") {

    std::cout << "\nRtaudio"
                 "\n~~~~~~~" << std::endl;

    System::LibRtAudio system{};

    for (auto device : system.getDevices()) {

        std::cout << device
                << std::endl;
    }


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

TEST_CASE("PortAudio", "[Spectrogram::Audio::System::LibPortAudio]") {

    std::cout << "\nPortAudio"
                 "\n~~~~~~~~~" << std::endl;

    System::LibPortAudio system{};

    for (auto device : system.getDevices()) {

        std::cout << device
                  << std::endl;
    }

}

TEST_CASE("PulseAudio", "[Spectrogram::Audio::System::LibPulseAudio]") {

    std::cout << "\nPulseAudio"
                 "\n~~~~~~~~~" << std::endl;

    System::LibPulseAudio system{};

    for (auto device : system.getDevices()) {

        std::cout << device
                  << std::endl;
    }

}
