#ifndef SPECTROGRAM_GRAPH_H
#define SPECTROGRAM_GRAPH_H

#include <QtWidgets>
#include "qcustomplot.h"
#include <QTimer>

#include <Spectrogram/Audio/Buffer.h>
#include <Spectrogram/Audio/System/Blocking.h>
#include <Spectrogram/Audio/Backend/Soundio.h>

#include <Spectrogram/Fourier/processor.h>

using namespace Spectrogram;
using namespace Spectrogram::Audio;

class SpectrogramGraph : public QCustomPlot {
Q_OBJECT

public:
    explicit SpectrogramGraph(QWidget *parent = 0);
    ~SpectrogramGraph();

    void setYAxisLog();
    void setupRealTimeColorMap();

public slots:
    void realtimeColorSlot();

private:
    void createColorScale();

    Channel getNewChannel();

    QCPColorMap *colorMap;

    int yAxisSize;
    int xAxisSize;
    QTimer *dataTimer;

    Buffer buffer;
    System::Blocking audioSystem;
    Fourier::Processor audioProcessor{};
};

#endif // SPECTROGRAM_GRAPH_H