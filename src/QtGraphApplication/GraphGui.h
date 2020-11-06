#ifndef GRAPH_GUI_H
#define GRAPH_GUI_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QTimer>

#include <Spectrogram/Audio/Buffer.h>
#include <Spectrogram/Audio/System/Blocking.h>
#include <Spectrogram/Audio/Backend/Soundio.h>

#include <Spectrogram/Fourier/processor.h>

using namespace Spectrogram;
using namespace Spectrogram::Audio;

class GraphGui : public QMainWindow {
Q_OBJECT

public:
    explicit GraphGui(QWidget *parent = 0);
    ~GraphGui();

    void setYAxisLog();
    void setupRealTimeColorMap();

public slots:

    void realtimeColorSlot();

private:
    void createColorScale();

    Channel getNewChannel();


    QCustomPlot *customPlot;
    QCPColorMap *colorMap;

    int yAxisSize;
    int xAxisSize;
    QTimer *dataTimer;

    Buffer buffer;
    System::Blocking audioSystem;
    Fourier::Processor audioProcessor{};


};

#endif // GRAPH_GUI_H