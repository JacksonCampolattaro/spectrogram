//
// Created by jackcamp on 10/11/20.
//

#ifndef SPECTROGRAM_MONOLITHICSYSTEM_H
#define SPECTROGRAM_MONOLITHICSYSTEM_H

#include <Spectrogram/Audio/Buffer.h>
#include <Spectrogram/Audio/DeviceList.h>

#include <soundio/soundio.h>

#include <boost/lockfree/spsc_queue.hpp>
#include <condition_variable>

#include <vector>
#include <memory>

namespace Spectrogram::Audio {

    class MonolithicSystem {

    public:

        MonolithicSystem();

        DeviceList &devices();

        void start(const Device &device);

        Buffer getBuffer(size_t frames);

        void stop();

        template<typename DataType>
        static const SoundIoFormat sampleTypeToFormat() {

            if constexpr (std::is_same<DataType, float>::value)
                return SoundIoFormatFloat32NE;

            if constexpr (std::is_same<DataType, double>::value)
                return SoundIoFormatFloat64NE;

            if constexpr (std::is_same<DataType, int16_t>::value)
                return SoundIoFormatS16LE;

            if constexpr (std::is_same<DataType, int32_t>::value)
                return SoundIoFormatS32LE;

            return SoundIoFormatInvalid;
        }

        typedef boost::lockfree::spsc_queue<Sample> ChannelQueue;
        typedef std::vector<std::unique_ptr<ChannelQueue>> ChannelQueues;

    private:

        SoundIo *_soundio = nullptr;
        SoundIoInStream *_inStream = nullptr;

        DeviceList _devices;

        ChannelQueues _channelQueues{};

    };

}

#endif //SPECTROGRAM_MONOLITHICSYSTEM_H
