#ifndef SPECTROGRAM_VISUALIZER_H
#define SPECTROGRAM_VISUALIZER_H

#include <Spectrogram/Audio/Buffer.h>

namespace Spectrogram::Visualizer {

    class Visualizer {
    public:

        virtual void draw(const Audio::Buffer &buffer) = 0;

    };


}

#endif //SPECTROGRAM_VISUALIZER_H
