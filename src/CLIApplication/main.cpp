
#include <Spectrogram/Audio/System/Blocking.h>
#include <Spectrogram/Audio/Backend/Soundio.h>
#include <Spectrogram/Audio/Backend/Dummy.h>

#include <iostream>
#include <memory>

using namespace Spectrogram::Audio;

int main() {

    // Initialize the system
    auto system = System::Blocking(std::make_unique<Backend::Soundio>());
    //auto system = System::Blocking(std::make_unique<Backend::Dummy>(1200));

    // List the devices
    std::cout << "Devices:" << std::endl;
    for (const auto &device : system.devices())
        std::cout << device << std::endl;

    int device = 2;
    std::cout << "\nInput device" << std::endl;
    std::cout << system.devices()[device] << std::endl;
    system.start(system.devices()[device], std::chrono::seconds(30));

    Buffer buffer;
    buffer.channels().resize(system.devices()[device].channelCount);
    for (auto &channel : buffer.channels())
        channel.resize(200);

    for (int i = 0; i < 10000; ++i) {

        system.fillBuffer(buffer);

        auto frameRange = buffer.frames();
        for (auto frame : frameRange) {

            for (auto sample : frame) {

                std::string view = "                                   |                                   ";
                view.replace(view.size() * (sample + 1) / 2, 1, "*");
                std::cout << view;
            }
            std::cout << "\n";
        }
        std::cout << std::endl;

//        for (size_t sampleIndex = 0; sampleIndex < buffer.channels()[0].size(); sampleIndex += 1) {
//
//            for (auto channel : buffer.channels()) {
//
//                auto sample = channel[sampleIndex];
//
//                std::string view = "                                   |                                   ";
//                view.replace(view.size() * (sample + 1) / 2, 1, "*");
//
//                std::cout << view;
//            }
//            std::cout << "\n";
//        }
//        std::cout << std::endl;

    }

    system.stop();

    return EXIT_SUCCESS;
}
