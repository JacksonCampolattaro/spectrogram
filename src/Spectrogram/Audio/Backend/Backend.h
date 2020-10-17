#ifndef SPECTROGRAM_BACKEND_H
#define SPECTROGRAM_BACKEND_H

#include <Spectrogram/Audio/Buffer.h>
#include <Spectrogram/Audio/DeviceList.h>

#include <functional>

/**
 * @brief Contains all audio backend implementations
 */
namespace Spectrogram::Audio::Backend {

    /**
     * @brief An abstract class that defines the functionality a backend should provide
     *
     * This is meant to be subclassed for various backend libraries.
     * @todo
     */
    class Backend {
    public:

        typedef std::function<void(const std::vector<Device> &)> DevicesChangedCallback;
        typedef std::function<void(const std::vector<Sample *> &arrays, size_t length)> NewSamplesCallback;

        /**
         * @brief a method to find out which devices are available as inputs
         *
         * @todo
         *
         * @return a DeviceList containing the available input devices
         */
        virtual DeviceList &devices() = 0;

        /**
         * @brief Starts the requested device, information read will be sent the provided callback
         *
         * @todo
         *
         * @param device the source to read from
         * @param frames the number of frames to include in a buffer
         * @param callback the callback used for processing new data
         */
        virtual void start(const Device &device, size_t frames, NewSamplesCallback callback) = 0;

        /**
         * @brief Stops the currently running device, safely closing the input stream
         *
         * @todo
         */
        virtual void stop() = 0;

    };
}

#endif //SPECTROGRAM_BACKEND_H
