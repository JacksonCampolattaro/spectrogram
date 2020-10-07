
#include <catch2/catch.hpp>

#include <Spectrogram/Audio/System/System.h>
#include <Spectrogram/Audio/System/Blocking.h>

#include <Spectrogram/Audio/Backend/Dummy.h>

#include <iostream>
#include <unistd.h>

using namespace Spectrogram::Audio;

TEST_CASE("Dummy devices", "[Dummy]") {

    auto system = System::Blocking(std::make_unique<Backend::Dummy>());

    Device d{"test", 0, false};
    system.start(d);

    for (auto channel : system.getBuffer()) {
        for (auto sample : channel) {
            std::cout << sample << "\t";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;


    system.stop();
}
