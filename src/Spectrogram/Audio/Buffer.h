#ifndef SPECTROGRAM_BUFFER_H
#define SPECTROGRAM_BUFFER_H

#include <utility>
#include <vector>

#include <boost/iterator/iterator_facade.hpp>

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

    typedef std::vector<Sample> Frame;

    class FrameIter;

    class FrameRange;

    class Buffer {
    public:

        /**
         * @brief
         *
         * @todo
         */
        typedef std::vector<Channel> ChannelRange;

        [[nodiscard]] size_t numFrames() const;

        [[nodiscard]] size_t numChannels() const;

        [[nodiscard]] FrameRange frames();

        [[nodiscard]] ChannelRange &channels();

        [[nodiscard]] ChannelRange const &channels() const;

    private:

        ChannelRange _channels;
    };

    class FrameIter :
            boost::iterator_facade<FrameIter, Frame, boost::forward_traversal_tag> {
    public:

    private:

        friend class boost::iterator_core_access;

        friend class FrameRange;

        explicit FrameIter(std::vector<Channel::const_iterator> sampleIterators) :
                _sampleIterators(std::move(sampleIterators)) {}

        void increment() {
            for (auto &iter : _sampleIterators)
                iter++;
        }

        bool equal(FrameIter const &other) {
            return _sampleIterators[0] == other._sampleIterators[0];
        }

        [[nodiscard]] Frame dereference() const {
            Frame frame;
            for (auto &iter : _sampleIterators)
                frame.push_back(*iter);
            return frame;
        }

        std::vector<Channel::const_iterator> _sampleIterators;
    };

    class FrameRange {
    public:

        FrameIter begin() {
            std::vector<Channel::const_iterator> sampleIterators;
            for (auto channel : _buffer.channels())
                sampleIterators.emplace_back(channel.begin());
            return FrameIter(sampleIterators);
        }

        FrameIter end() {
            std::vector<Channel::const_iterator> sampleIterators;
            for (auto channel : _buffer.channels())
                sampleIterators.emplace_back(channel.end());
            return FrameIter(sampleIterators);
        }

    private:

        friend class Buffer;

        explicit FrameRange(Buffer &buffer) :
                _buffer(buffer) {}

        Buffer &_buffer;

    };

}


#endif //SPECTROGRAM_BUFFER_H
