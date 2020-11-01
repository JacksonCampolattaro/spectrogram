#ifndef SPECTROGRAM_BUFFER_H
#define SPECTROGRAM_BUFFER_H

#include <vector>

namespace Spectrogram::Audio {

    /**
     * @brief A sample represents a single data point in the audio stream
     *
     * @todo
     */
    typedef float Sample;

    /**
     * @brief A channel is the collection of samples in a single channel for a fixed length of time.
     *
     * Most audio sources have a left and right channel
     */
    typedef std::vector<Sample> Channel;

    class Buffer {
    public:

        /**
         * @brief
         *
         * @todo
         */
        typedef std::vector<Channel> ChannelRange;

        ChannelRange channels;

    };

}


#endif //SPECTROGRAM_BUFFER_H
