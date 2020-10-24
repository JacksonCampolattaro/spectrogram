#ifndef SPECTROGRAM_EVENT_H
#define SPECTROGRAM_EVENT_H

#include <Spectrogram/Audio/System/System.h>

#include <boost/lockfree/spsc_queue.hpp>
#include <condition_variable>
#include <deque>

namespace Spectrogram::Audio::System {

    class Event : protected System {
    public:

        explicit Event(std::unique_ptr<Backend::Backend> backend);

        void start(const Device &device, std::chrono::milliseconds maxLatency, size_t bufferLength);

        using System::devices;
        using System::stop;

        void pushSamples(const std::vector<Sample> &array) override;

        virtual void newDataNotification() = 0;

        typedef boost::lockfree::spsc_queue<Sample> ChannelQueue;

    protected:

        using System::start;

        std::deque<ChannelQueue> _channelQueues;

        Buffer _buffer;

    };

}


#endif //SPECTROGRAM_EVENT_H
