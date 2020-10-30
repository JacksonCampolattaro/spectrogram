#ifndef SPECTROGRAM_EVENT_H
#define SPECTROGRAM_EVENT_H

#include <Spectrogram/Audio/System/System.h>

#include <boost/lockfree/spsc_queue.hpp>
#include <condition_variable>
#include <deque>

namespace Spectrogram::Audio::System {

    class Event : public System {
    public:

        explicit Event(std::unique_ptr<Backend::Backend> backend);

        using System::devices;

        void start(const Device &device, std::chrono::milliseconds maxLatency, size_t bufferLength);
        using System::stop;

        void pushSamples(const std::vector<Sample> *array) override;

        typedef boost::lockfree::spsc_queue<Sample> ChannelQueue;

    protected:

        virtual void notifyNewData() = 0;
        virtual void processNewData() = 0;

        virtual bool newDataAvailable();
        virtual const Buffer &retrieveNewData();

        std::deque<ChannelQueue> _channelQueues;

        Buffer _buffer;

    private:

        using System::start;

    };

}

#endif //SPECTROGRAM_EVENT_H
