#ifndef SPECTROGRAM_BLOCKING_H
#define SPECTROGRAM_BLOCKING_H

#include <Spectrogram/Audio/System/System.h>

#include <boost/lockfree/spsc_queue.hpp>
#include <condition_variable>

namespace Spectrogram::Audio::System {

    class Blocking : public System {
    public:

        Blocking(std::unique_ptr<Backend::Backend> backend);

        Buffer getBuffer();

        void pushSamples(std::vector<Sample *> arrays, size_t length) override;

    private:

        boost::lockfree::spsc_queue<Buffer> _bufferQueue{16};
        std::condition_variable _bufferAdded;

    };
}

#endif //SPECTROGRAM_BLOCKING_H
