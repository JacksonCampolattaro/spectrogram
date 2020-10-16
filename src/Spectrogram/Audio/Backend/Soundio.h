//
// Created by jackcamp on 10/6/20.
//

#ifndef SPECTROGRAM_SOUNDIO_H
#define SPECTROGRAM_SOUNDIO_H

#include <Spectrogram/Audio/Backend/Backend.h>
#include <soundio/soundio.h>

namespace Spectrogram::Audio::Backend {

    /**
     * @brief A backend implementation based on the cross-platform audio library [Soundio](http://libsound.io/).
     */
    class Soundio : public Backend {

    public:

        /**
         * @brief Simple constructor which initializes the underlying library
         */
        Soundio();

        DeviceList &devices() override;

        void start(const Device &device, size_t frames, NewSamplesCallback callback) override;

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

        DeviceList _devices{};
    };

}


#endif //SPECTROGRAM_SOUNDIO_H
