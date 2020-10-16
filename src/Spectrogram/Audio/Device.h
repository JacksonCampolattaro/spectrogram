#ifndef SPECTROGRAM_DEVICE_H
#define SPECTROGRAM_DEVICE_H

#include <string>
#include <utility>
#include <iostream>

namespace Spectrogram::Audio {

    /**
     * @brief a reification of the system's audio sources, designed to be compatible with different backends.
     */
    struct Device {

        Device(std::string name, int id, bool isDefault, size_t channelCount) :
                name(std::move(name)), id(id), isDefault(isDefault), channelCount(channelCount) {}

        std::string name;
        int id;
        bool isDefault;
        size_t channelCount;

        friend std::ostream &operator<<(std::ostream &os, const Device &device) {

            os << device.id << ": ";
            os << (device.isDefault ? "* " : "  ");
            os << "\"" << device.name << "\"";

            return os;
        }
    };

}

#endif //SPECTROGRAM_DEVICE_H
