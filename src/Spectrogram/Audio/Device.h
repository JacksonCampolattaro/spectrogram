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

        std::string name;
        int id;
        bool isDefault;
        size_t channelCount;
        size_t sampleRate;

        /**
         * @brief This allows directly writing the device's info to an output stream, useful for debugging
         * @param os The output stream to write to
         * @param device The device to write
         * @return the output stream (for chained invocations)
         */
        friend std::ostream &operator<<(std::ostream &os, const Device &device) {

            os << device.id << ": ";
            os << (device.isDefault ? "* " : "  ");
            os << "\"" << device.name << "\"";

            return os;
        }
    };

}

#endif //SPECTROGRAM_DEVICE_H
