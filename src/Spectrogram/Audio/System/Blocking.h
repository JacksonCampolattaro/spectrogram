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
    class Blocking : public System {
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
         * @brief Returns a buffer full of samples as soon as they become available.
         *
         * Blocks until one buffer's length worth of samples is available.
         * The approach to blocking may be a source of latency.
         *
         * @return the new buffer
         */
        void getBuffer(Buffer &buffer);

        void start(const Device &device) override;

        void pushSamples(const std::vector<Sample *> &arrays, size_t length) override;

        typedef boost::lockfree::spsc_queue<Sample> ChannelQueue;

    private:

        std::deque<ChannelQueue> _channelQueues;
        std::condition_variable _samplesAdded;
        size_t _frames;

    };
}

#endif //SPECTROGRAM_BLOCKING_H
