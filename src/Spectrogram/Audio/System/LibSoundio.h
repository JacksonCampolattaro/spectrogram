#ifndef SPECTROGRAM_LIBSOUNDIO_H
#define SPECTROGRAM_LIBSOUNDIO_H

#include <Spectrogram/Audio/System/System.h>

#include <soundio/soundio.h>

#include <iostream>

namespace Spectrogram::Audio::System {

    class LibSoundio : public System {
    public:

        LibSoundio();

        ~LibSoundio();

        void setBufferSize(size_t size) override;

        Buffer getBuffer() override;

        std::vector<Device> getDevices() override;

        void setDevice(Device &device) override;

    private:

        SoundIo *_soundio;
        SoundIoInStream *_inStream;

    };

    template <typename DataType>
    SoundIoFormat sampleTypeToFormat() {

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
}


#endif //SPECTROGRAM_LIBSOUNDIO_H
