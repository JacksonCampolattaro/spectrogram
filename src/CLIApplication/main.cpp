
#include <Spectrogram/Audio/System/Blocking.h>
#include <Spectrogram/Audio/Backend/Soundio.h>
#include <Spectrogram/Audio/Backend/Dummy.h>

#include <iostream>
#include <memory>

using namespace Spectrogram::Audio;

int main() {

    // Initialize the system
//    auto system = System::Blocking(std::make_unique<Backend::Soundio>());
    auto system = System::Blocking(std::make_unique<Backend::Dummy>(1200));


    // List the devices
    std::cout << "Devices:" << std::endl;
    for (const auto &device : system.devices())
        std::cout << device << std::endl;

    int device = 0;
    std::cout << "\nInput device" << std::endl;
    std::cout << system.devices()[device] << std::endl;
    system.start(system.devices()[device]);

    for (int i = 0; i < 100; ++i) {

        auto buffer = system.getBuffer();
        for (int sampleIndex = 0; sampleIndex < buffer[0].size(); ++sampleIndex) {

            for (int channel = 0; channel < buffer.size(); ++channel) {

                auto sample = buffer[channel][sampleIndex];

                std::string view = "               |               ";
                view.replace(view.size() * (sample + 1) / 2, 1, "*");

                std::cout << view;
            }
            std::cout << std::endl;
        }

    }

    system.stop();

    return EXIT_SUCCESS;
}
