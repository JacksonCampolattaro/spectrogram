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

        void fillBuffer(Buffer &buffer);

        void start(const Device &device, std::chrono::milliseconds maxLatency);
        void pushSamples(const std::vector<Sample *> &arrays, size_t length) override;
        using System::devices;
        using System::stop;

        typedef boost::lockfree::spsc_queue<Sample> ChannelQueue;

    protected:

        using System::start;

        std::deque<ChannelQueue> _channelQueues;
        std::condition_variable _samplesAdded;

    };

}


#endif //SPECTROGRAM_EVENT_H
