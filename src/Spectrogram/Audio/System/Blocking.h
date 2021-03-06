#ifndef SPECTROGRAM_BLOCKING_H
#define SPECTROGRAM_BLOCKING_H

#include <Spectrogram/Audio/System/System.h>

#include <boost/lockfree/spsc_queue.hpp>
#include <condition_variable>
#include <deque>

namespace Spectrogram::Audio::System {

    /**
     * @brief A system providing an simpler way of interacting with the backend (no callbacks necessary)
     *
     * Simpler interaction may be at the expense of performance.
     * This is useful for a minimum viable product, (for example, the CLI application),
     * but a full application should use a more event-oriented subclass of System.
     */
    class Blocking : protected System {
    public:

        /**
         * @brief A system object is constructed from the backend it will use
         *
         * The backend is passed using a unique_ptr so that it can be chosen at runtime.
         * A reference isn't used because the system takes ownership over the backend.
         *
         * @param backend The backend to pull data from
         */
        explicit Blocking(std::unique_ptr<Backend::Backend> backend);

        /**
         * @brief Fills a buffer with samples
         *
         * The number of samples to read is determined by the size of the buffer passed in.
         * Blocks until one buffer's length worth of samples is available.
         * The approach to blocking may be a source of latency.
         *
         * @param buffer the buffer to fill
         */
        void fillBuffer(Buffer &buffer);

        using System::devices;

        /**
         * @brief Starts the backend and prepares the data structures underlying the blocking system
         *
         * @param device The input device to connect to
         * @param maxLatency The maximum allowable latency before samples should start being dropped
         */
        void start(const Device &device, std::chrono::milliseconds maxLatency);

        using System::stop;

        void pushSamples(const std::vector<Sample> *array) override;

        typedef boost::lockfree::spsc_queue<Sample> ChannelQueue;

    protected:

        using System::start;

        std::deque<ChannelQueue> _channelQueues;
        std::condition_variable _samplesAdded;

    };
}

#endif //SPECTROGRAM_BLOCKING_H
