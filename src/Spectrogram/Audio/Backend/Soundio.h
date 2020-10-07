//
// Created by jackcamp on 10/6/20.
//

#ifndef SPECTROGRAM_SOUNDIO_H
#define SPECTROGRAM_SOUNDIO_H

#include <Spectrogram/Audio/Backend/Backend.h>
#include <soundio/soundio.h>

namespace Spectrogram::Audio::Backend {

    class Soundio : public Backend {

    public:

        Soundio();

        DeviceList &devices() override;

        void start(const Device &device, typename Backend::NewBufferCallback callback) override;

        void stop() override;

        template <typename DataType>
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

    private:

        SoundIo *_soundio;
        SoundIoInStream *_inStream;
        NewBufferCallback _callback;

        DeviceList _devices;

    };

}


#endif //SPECTROGRAM_SOUNDIO_H
