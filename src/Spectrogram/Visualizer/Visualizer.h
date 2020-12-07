#ifndef SPECTROGRAM_VISUALIZER_H
#define SPECTROGRAM_VISUALIZER_H

#include <Spectrogram/Audio/Buffer.h>

namespace Spectrogram::Visualizer {

    class Visualizer {
    public:

        virtual void draw([[maybe_unused]] const Audio::Buffer &buffer) {};

    };


}

#endif //SPECTROGRAM_VISUALIZER_H
