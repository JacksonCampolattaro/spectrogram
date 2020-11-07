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

    ~GraphGui();

    void setYAxisLog();

    void setupRealTimeColorMap();

public slots:

    void realtimeColorSlot();

//    void draw(const Fourier::FrequencyDomainBuffer &frequencyDomainBuffer);

private:

    void createColorScale();

    Fourier::FrequencyDomainBuffer getNewData();


    QCustomPlot *customPlot;
    QCPColorMap *colorMap;

    int yAxisSize;
    int xAxisSize;
    QTimer *dataTimer;

    Audio::Buffer buffer{};
    Audio::System::Blocking audioSystem;


};

#endif // GRAPH_GUI_H