#ifndef SPECTROGRAM_SYSTEM_H
#define SPECTROGRAM_SYSTEM_H

#include <Spectrogram/Audio/Backend/Backend.h>

#include <memory>


/**
 * @brief Contains all audio system implementations
 */
namespace Spectrogram::Audio::System {

    /**
     * @brief abstract wrapper class that provides simpler syntax when connecting to a backend
     */
    class System {
    public:

        /**
         * @brief A system object is constructed from the backend it will use
         *
         * The backend is passed using a unique_ptr so that it can be chosen at runtime.
         * A reference isn't used because the system takes ownership over the backend.
         *
         * @param backend The backend to pull data from
         */
        explicit System(std::unique_ptr<Backend::Backend> backend);

        /**
         * @brief Forwards the device list from the backend
         * @return the collection of available audio input devices
         */
        const DeviceList &devices();

        /**
         * @brief Starts the backend
         *
         * After this is called the pushSamples method will be invoked by the backend
         * whenever new audio data becomes available
         *
         * @param device the device to connect to
         */
        virtual void start(const Device &device);

        /**
         * @brief Stops the backend
         */
        void stop();

        /**
         * @brief Callback for processing new samples
         *
         * This function is provided to the backend as an std::function and called whenever new data is available.
         * When you subclass the System class, override this to do what you'd like with the samples.
         *
         * @param arrays N pointers to c-style arrays of samples, where N is the number of channels
         * @param length the length of the arrays (length is nondeterministic, but common between the arrays)
         */
        virtual void pushSamples(const std::vector<Sample *> &arrays, size_t length) = 0;

    private:

        std::unique_ptr<Backend::Backend> _backend;
    };

}

#endif //SPECTROGRAM_SYSTEM_H
