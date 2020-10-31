#ifndef SPECTROGRAM_EVENT_H
#define SPECTROGRAM_EVENT_H

#include <Spectrogram/Audio/System/System.h>

#include <boost/lockfree/spsc_queue.hpp>
#include <condition_variable>
#include <deque>

namespace Spectrogram::Audio::System {

    /**
     * @brief Event-oriented interface for an audio backend, intended to be subclassed
     */
    class Event : public System {
    public:

        /**
         * @brief This initializes the backend, as well as the data structures which enable event-driven use
         *
         * Make sure to extend this constructor when you subclass this!
         *
         * @param backend The audio backend to be used
         */
        explicit Event(std::unique_ptr<Backend::Backend> backend);

        /**
         * @todo This doesn't mesh super well with an event-driven architecture!
         */
        using System::devices;

        /**
         * @brief Starts the backend, so that data begins to become available
         *
         * @param device The device to listen to
         * @param maxLatency The maximum allowable latency (time) before loss of data should occur
         * @param bufferLength The length of the buffer which should be produced
         */
        void start(const Device &device, std::chrono::milliseconds maxLatency, size_t bufferLength);

        /**
         * @brief Stops the backend safely
         */
        using System::stop;

    protected:

        /**
         * @brief Invoked whenever new data becomes available (but not necessarily a buffer's worth!)
         *
         * You should subclass this, and use it to send a signal connected to checkForNewData().
         * Keep in mind that everything you put in here is subject to a real-time constraint.
         * That means that you'll have to think carefully about the type of signal you use!
         */
        virtual void notifyNewData() = 0;

        /**
         * @brief Invoked automatically whenever a new buffer is available
         *
         * You should subclass this and use it to trigger actions when new buffers are available.
         * Code in here is run in the main event loop of your system of choice,
         * which means it's not subject to a real-time constraint, but speed still matters!
         *
         * Though it's technically possible, I don't recommend putting visualization code inside this function.
         * It's better for this to simply emit a signal containing the buffer.
         * Then your visualization system can have a slot that lets it update every time a new buffer is ready!
         *
         * @param buffer the newly available buffer
         */
        virtual void processNewData(const Buffer &buffer) = 0;

        /**
         * @brief Determines whether a buffer's worth of new samples is available, and processes it if necessary
         *
         * You should hook a cross-thread signal up to this.
         */
        void checkForNewData();

    private:

        using System::start;

        void pushSamples(const std::vector<Sample> *array) override;

        typedef boost::lockfree::spsc_queue<Sample> ChannelQueue;

        std::deque<ChannelQueue> _channelQueues;

        std::unique_ptr<Buffer> _buffer;

    };

}

#endif //SPECTROGRAM_EVENT_H
