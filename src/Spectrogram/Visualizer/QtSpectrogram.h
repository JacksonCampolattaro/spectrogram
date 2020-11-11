#ifndef SPECTROGRAM_QTSPECTROGRAM_H
#define SPECTROGRAM_QTSPECTROGRAM_H

#include "qcustomplot.h"
#include <QThread>

#include <Spectrogram/Audio/Buffer.h>
#include <Spectrogram/Audio/System/Blocking.h>
#include <Spectrogram/Audio/Backend/Soundio.h>

#include <Spectrogram/Fourier/FrequencyDomainBuffer.h>
#include "Spectrogram/PNG/Writer.h"

using namespace Spectrogram;

class QtSpectrogram : public QCustomPlot  {
Q_OBJECT

public:
    explicit QtSpectrogram(QWidget *parent = 0);
    ~QtSpectrogram();

public slots:

    void draw(const Audio::Buffer &buffer);
    void saveSnapShotPressed();
    void onWritingDone(bool success);

signals:
    void writeSnapShot();
    void snapShotWritingDone(bool success, QString filename);

private:
    void setupPngWriter();
    void shiftData();

    void addData(const Fourier::FrequencyDomainBuffer &frequencyDomainBuffer);

    QCPColorMap *colorMap;

    int yAxisSize = 700;
    int xAxisSize = 200;

    QThread writerThread;
	Spectrogram::PNG::Writer *pngWriter;

};

#endif // SPECTROGRAM_QTSPECTROGRAM_H