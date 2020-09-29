
#include <catch2/catch.hpp>

#include <Spectrogram/Audio/System.h>

#include <portaudio.h>

TEST_CASE("Connecting to system audio", "[Audio::System]") {
//
//    Audio::System system;
//
//    std::cout << system._rtAudio.getDeviceCount() << " Devices" << std::endl;
}

TEST_CASE("Printing out all devices", "[Audio::System]") {
//
//    Audio::System system;
//
//    system.devices();
}

TEST_CASE("Printing out all devices with portaudio", "[Audio::System]") {
//
//    Pa_Initialize();
//    std::cout << Pa_GetDeviceCount() << std::endl;
//    for (int i = 0; i < Pa_GetDeviceCount(); ++i) {
//        std::cout << Pa_GetDeviceInfo(i)->name << std::endl;
//    }
//
}

TEST_CASE("Printing out all devices with libsoundio", "[Audio::System]") {
//
//    auto soundio = soundio_create();
//    std::cout << soundio_output_device_count(soundio) << std::endl;
}
