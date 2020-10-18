
#include <catch2/catch.hpp>

#include <Spectrogram/Audio/System/System.h>
#include <Spectrogram/Audio/System/Blocking.h>

#include <Spectrogram/Audio/Backend/Dummy.h>

#include <iostream>
#include <unistd.h>

using namespace Spectrogram::Audio;

TEST_CASE("Dummy devices", "[Dummy]") {

    auto system = System::Blocking(std::make_unique<Backend::Dummy>(440));

    system.start(system.devices()[0]);

    Buffer buffer;
    buffer.resize(system.devices()[0].channelCount);
    for (auto &channel : buffer)
        channel.resize(200);

    system.fillBuffer(buffer);
    for (auto channel : buffer) {
        for (auto sample : channel) {
            std::cout << sample << "\t";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;


    system.stop();
}
