#ifndef SPECTROGRAM_QTSPECTROGRAM_H
#define SPECTROGRAM_QTSPECTROGRAM_H

#include "qcustomplot.h"
#include <QThread>

#include <Spectrogram/Audio/Buffer.h>
#include <Spectrogram/Audio/System/Blocking.h>
#include <Spectrogram/Audio/Backend/Soundio.h>

#include <Spectrogram/Fourier/FrequencyDomainBuffer.h>
#include "Spectrogram/PNG/Writer.h"
#include "Spectrogram/Settings/Profile.h"

using namespace Spectrogram;

class QtSpectrogram : public QCustomPlot  {
Q_OBJECT

public:
    explicit QtSpectrogram(QWidget *parent = 0);
    ~QtSpectrogram();

public slots:
    void draw(const Audio::Buffer &buffer);
    void onWritingDone(bool success);
    void startSavePressed();
    void stopSavePressed();
    void changeSettings(const Settings::Profile &settings);

signals:
    void pngWritingDone(bool success, QString filename);
    void startSaving();
    void stopSaving();
    void updateSave();

private:
    void setupYAxisLogScale();
    void setupYAxisLinearScale();
    void setupPngWriter();

    void changeColorGradient(int);
    void changeYScaleType(bool);

    void shiftData();

    void addData(const Fourier::FrequencyDomainBuffer &frequencyDomainBuffer);
    float getIntensity(const int &y, const Fourier::FrequencyDomainBuffer &frequencyDomainBuffer);
    double getLogValue(const int &y);
    double getLinearValue(const int &y);

    QCPColorMap *colorMap;

    int yAxisSize = 500;
    int xAxisSize = 200;

    bool logScale;

    QThread writerThread;
	Spectrogram::PNG::Writer *pngWriter;

};

#endif // SPECTROGRAM_QTSPECTROGRAM_H