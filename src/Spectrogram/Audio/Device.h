#ifndef SPECTROGRAM_DEVICE_H
#define SPECTROGRAM_DEVICE_H

#include <string>
#include <utility>

namespace Spectrogram::Audio {

    struct Device {

        Device(std::string name, int id, bool defaultOutput) :
                name(std::move(name)), id(id), defaultOutput(defaultOutput) {}

        std::string name;
        int id;
        bool defaultOutput;
    };

}

#endif //SPECTROGRAM_DEVICE_H
