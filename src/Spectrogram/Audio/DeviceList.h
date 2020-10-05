#ifndef SPECTROGRAM_DEVICELIST_H
#define SPECTROGRAM_DEVICELIST_H

#include <functional>

#include <Spectrogram/Audio/Device.h>

namespace Spectrogram::Audio {

    class DeviceList : private std::vector<Device> {
    public:

        // TODO: Accessor methods and iterators will be made available here

        // This will be called and
        void onDevicesChanged(const std::vector<Device> &devices);


    };

}


#endif //SPECTROGRAM_DEVICELIST_H
