#ifndef SPECTROGRAM_DEVICE_H
#define SPECTROGRAM_DEVICE_H

#include <string>
#include <utility>
#include <iostream>

namespace Spectrogram::Audio {

    struct Device {

        Device(std::string name, int id, bool isDefault, bool isInput) :
                name(std::move(name)), id(id), isDefault(isDefault), isInput(isInput) {}

        std::string name;
        int id;
        bool isDefault;
        bool isInput;

        friend std::ostream &operator<<(std::ostream &os, const Device &device) {

            os << device.id << ": ";
            os << (device.isInput ? "I" : "O");
            os << (device.isDefault ? "* " : "  ");
            os << "\"" << device.name << "\"";

            return os;
        }
    };

}

#endif //SPECTROGRAM_DEVICE_H
