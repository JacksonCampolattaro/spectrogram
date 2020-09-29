
#include <catch2/catch.hpp>

#include <portaudio.h>
#include <soundio/soundio.h>

#include <Spectrogram/Audio/System/System.h>
#include <Spectrogram/Audio/System/LibRtAudio.h>

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

        std::cout << device.name << std::endl;
    }


}

TEST_CASE("Printing out all devices with portaudio", "[Audio::System]") {

    std::cout << "\nPortaudio\n"
                 "~~~~~~~~~" << std::endl;

    Pa_Initialize();
    std::cout << Pa_GetDeviceCount() << std::endl;
    for (int i = 0; i < Pa_GetDeviceCount(); ++i) {
        std::cout << Pa_GetDeviceInfo(i)->name << std::endl;
    }

}

TEST_CASE("Printing out all devices with libsoundio", "[Audio::System]") {

    std::cout << "\nLibsoundio\n"
                 "~~~~~~~~~~" << std::endl;
    auto soundio = soundio_create();
    REQUIRE(soundio);
    REQUIRE(!soundio_connect(soundio));
    soundio_flush_events(soundio);
    std::cout << "Output devices:" << std::endl;
    for (int i = 0; i < soundio_output_device_count(soundio); ++i) {
        auto device = soundio_get_output_device(soundio, i);
        std::cout << "\t" << device->name << std::endl;
    }
    std::cout << "Input devices:" << std::endl;
    for (int i = 0; i < soundio_input_device_count(soundio); ++i) {
        auto device = soundio_get_input_device(soundio, i);
        std::cout << "\t" << device->name << std::endl;
    }
    std::cout << "Default output:" << std::endl;
    int d = soundio_default_output_device_index(soundio);
    auto device = soundio_get_input_device(soundio, d);
    std::cout << "\t" << device->name << std::endl;
}
