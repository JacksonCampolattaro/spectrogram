#ifndef GRAPH_GUI_H
#define GRAPH_GUI_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QTimer>

#include <Spectrogram/Audio/Buffer.h>
#include <Spectrogram/Audio/System/Blocking.h>
#include <Spectrogram/Audio/Backend/Soundio.h>

#include <Spectrogram/Fourier/FrequencyDomainBuffer.h>

using namespace Spectrogram;

class GraphGui : public QMainWindow {
Q_OBJECT

public:
    explicit GraphGui(QWidget *parent = 0);

    void setYAxisLog();

    void setupRealTimeColorMap();

public slots:

    void draw(const Audio::Buffer &buffer);

private:

    void createColorScale();

    void setupPlot(size_t xSize, size_t ySize);

    QCustomPlot *customPlot;
    QCPColorMap *colorMap;

    int yAxisSize = 2205;
    int xAxisSize = 800;

};

#endif // GRAPH_GUI_H