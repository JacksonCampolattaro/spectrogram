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

        std::vector<enum SoundIoFormat> _prioritizedAudioFormats = {
                SoundIoFormatFloat32NE,
                SoundIoFormatFloat32FE,
                SoundIoFormatS32NE,
                SoundIoFormatS32FE,
                SoundIoFormatS24NE,
                SoundIoFormatS24FE,
                SoundIoFormatS16NE,
                SoundIoFormatS16FE,
                SoundIoFormatFloat64NE,
                SoundIoFormatFloat64FE,
                SoundIoFormatU32NE,
                SoundIoFormatU32FE,
                SoundIoFormatU24NE,
                SoundIoFormatU24FE,
                SoundIoFormatU16NE,
                SoundIoFormatU16FE,
                SoundIoFormatS8,
                SoundIoFormatU8,
                SoundIoFormatInvalid
        };

        std::vector<int> _prioritizedSampleRates = {
                48000,
                44100,
                96000,
                24000,
                0
        };
    };
}


#endif //SPECTROGRAM_LIBSOUNDIO_H
