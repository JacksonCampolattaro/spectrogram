#ifndef SPECTROGRAM_QTSPECTROGRAM_H
#define SPECTROGRAM_QTSPECTROGRAM_H

#include "qcustomplot.h"

#include <Spectrogram/Audio/Buffer.h>
#include <Spectrogram/Audio/System/Blocking.h>
#include <Spectrogram/Audio/Backend/Soundio.h>

#include <Spectrogram/Fourier/FrequencyDomainBuffer.h>

using namespace Spectrogram;

class QtSpectrogram : public QCustomPlot  {
Q_OBJECT

public:
    explicit QtSpectrogram(QWidget *parent = 0);

public slots:

    void draw(const Audio::Buffer &buffer);

private:

    void shiftData();

    void addData(const Fourier::FrequencyDomainBuffer &frequencyDomainBuffer);
    
    QCPColorMap *colorMap;

    int yAxisSize = 700;
    int xAxisSize = 200;

};

#endif // SPECTROGRAM_QTSPECTROGRAM_H