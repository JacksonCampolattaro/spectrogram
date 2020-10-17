#ifndef SPECTROGRAM_DEVICELIST_H
#define SPECTROGRAM_DEVICELIST_H

#include <functional>

#include <Spectrogram/Audio/Device.h>

namespace Spectrogram::Audio {

    /**
     * @brief A collection of all the input devices available for reading from
     *
     * @todo Eventually this should update itself using callbacks
     */
    class DeviceList : private std::vector<Device> {
    public:

        typedef std::vector<Device> vector;

        using vector::vector;
        using vector::emplace_back;
        using vector::begin;
        using vector::end;
        using vector::operator[];

        // TODO: Accessor methods and iterators will be made available here

        // This will be called and
        void onDevicesChanged(const std::vector<Device> &devices);


    };

}


#endif //SPECTROGRAM_DEVICELIST_H
