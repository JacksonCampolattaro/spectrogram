#ifndef SPECTROGRAM_BLOCKING_H
#define SPECTROGRAM_BLOCKING_H

#include <Spectrogram/Audio/System/System.h>

#include <boost/lockfree/spsc_queue.hpp>
#include <condition_variable>
#include <deque>

namespace Spectrogram::Audio::System {

    class Blocking : public System {
    public:

        explicit Blocking(std::unique_ptr<Backend::Backend> backend);

        void start(const Device &device, size_t frames) override;

        Buffer getBuffer();

        void pushSamples(const std::vector<Sample *> &arrays, size_t length) override;

        typedef boost::lockfree::spsc_queue<Sample> ChannelQueue;

    private:

        std::deque<ChannelQueue> _channelQueues;
        std::condition_variable _samplesAdded;
        size_t _frames;

    };
}

#endif //SPECTROGRAM_BLOCKING_H
