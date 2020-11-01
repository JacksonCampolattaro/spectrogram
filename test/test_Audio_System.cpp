
#include <catch2/catch.hpp>

#include <Spectrogram/Audio/System/System.h>
#include <Spectrogram/Audio/System/Blocking.h>

#include <Spectrogram/Audio/Backend/Dummy.h>
#include <Spectrogram/Audio/Backend/Soundio.h>

#include <iostream>

using namespace Spectrogram::Audio;

TEST_CASE("Dummy devices", "[Dummy]") {

    auto system = System::Blocking(std::make_unique<Backend::Dummy>(440));
    auto device = system.devices()[0];

//    system.start(device, std::chrono::seconds(2));
//
//    Buffer buffer(device, 200);
//
//    system.fillBuffer(buffer);
//    for (auto channel : buffer.channels()) {
//        for (auto sample : channel) {
//            std::cout << sample << "\t";
//        }
//        std::cout << "\n";
//    }
//    std::cout << std::endl;
//
//
//    system.stop();
}
