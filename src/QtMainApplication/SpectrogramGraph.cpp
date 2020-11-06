#include "SpectrogramGraph.h"
#include <QSharedPointer>

#define TO_KHZ 0.001

namespace SF = Spectrogram::Fourier;
namespace SA = Spectrogram::Audio;

SpectrogramGraph::SpectrogramGraph(QWidget *parent) :
        QCustomPlot(parent),
        audioSystem(std::make_unique<Backend::Soundio>()) {

    // Choose a device
    auto device = audioSystem.devices()[1];
    size_t channelLength = device.sampleRate; // when length == sampleRate, a buffer is 1 second long

    // Configure our buffer to hold the amount of data we want
    buffer.resize(device.channelCount);
    for (auto &channel : buffer)
        channel.resize(channelLength);

    // Tell the system to start listening to that device
    audioSystem.start(device, std::chrono::seconds(2));

    // Set up the audio processor, too
    audioProcessor.setSampleSize(channelLength);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    this->xAxis->setLabel("Time (?)");
    this->yAxis->setLabel("Frequency (kHz)");

    yAxisSize = channelLength / 2;
    xAxisSize = 10;

    setupRealTimeColorMap();
}

void SpectrogramGraph::createColorScale() {
    QCPColorScale *colorScale = new QCPColorScale(this);
    this->plotLayout()->addElement(0, 1, colorScale);
    colorScale->setLabel("dB change from baseline");
    colorMap->setColorScale(colorScale);

    QCPMarginGroup *group = new QCPMarginGroup(this);
    colorScale->setMarginGroup(QCP::msTop | QCP::msBottom, group);
    this->axisRect()->setMarginGroup(QCP::msTop | QCP::msBottom, group);
}

// TODO: Maybe this works right??? Not sure how to test
void SpectrogramGraph::setYAxisLog()
{
  /* To change the axis scale type from a linear scale to a logarithmic scale, 
   *  set QCPAxis::setScaleType to QCPAxis::stLogarithmic.
  */
  QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
  this->yAxis->setTicker(logTicker);
  this->yAxis->setScaleType(QCPAxis::stLogarithmic);

  colorMap->setDataScaleType(QCPAxis::stLogarithmic);
  colorMap->colorScale()->axis()->setTicker(logTicker);
  colorMap->colorScale()->setDataScaleType(QCPAxis::stLogarithmic);
}

void SpectrogramGraph::setupRealTimeColorMap() {

    // include this section to fully disable antialiasing for higher performance:
    this->setNotAntialiasedElements(QCP::aeAll);
    QFont font;
    font.setStyleStrategy(QFont::NoAntialias);
    this->xAxis->setTickLabelFont(font);

    colorMap = new QCPColorMap(this->xAxis, this->yAxis);

    createColorScale();

    //setYAxisLog();

    /* setSize(keysize as in xAxis, valuesize as in yAxis) */
    colorMap->data()->setKeySize(xAxisSize);
    colorMap->data()->setValueSize(yAxisSize);
    colorMap->data()->setRange(QCPRange(0, xAxisSize), QCPRange(0, yAxisSize * TO_KHZ));

    colorMap->data()->fill(0);
    colorMap->setGradient(QCPColorGradient::gpGrayscale);
    colorMap->rescaleDataRange(true);
    this->rescaleAxes();
    this->replot();

    dataTimer = new QTimer(this);
    // setup a timer that repeatedly calls SpectrogramGraph::realtimeColorSlot:
    QObject::connect(dataTimer, SIGNAL(timeout()), this, SLOT(realtimeColorSlot()));
    dataTimer->start(0); // Interval 0 means to refresh as fast as possible
}

void SpectrogramGraph::realtimeColorSlot() {
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed() / 1000.0; // time elapsed since start, in seconds
    static double lastPointKey = 0;
    SA::Channel newChannel = getNewChannel();
    if (key - lastPointKey > 0.01) // at most re-map every 10 ms
    {
        // make key axis range scroll with the data (at a constant range size of xAxisSize)
        colorMap->data()->setKeyRange(QCPRange(key, key+xAxisSize));
        for (int x = 0; x < xAxisSize; ++x) {
            for (int y = 0; y < yAxisSize; ++y) {
                // put new channel into the last column of the colormap
                if (x == xAxisSize - 1) {
                    colorMap->data()->setCell(x, y, (90.0f + newChannel[y]) / 90.0f);
                }
                // Shift all the channels down one
                else {
                    double newZ = colorMap->data()->cell(x + 1, y);
                    colorMap->data()->setCell(x, y, newZ);
                }
            }
        }
        colorMap->rescaleDataRange(true);
        this->rescaleAxes();
        //this->replot();
        lastPointKey = key;
    }
    this->replot();
}

SA::Channel SpectrogramGraph::getNewChannel() {

    audioSystem.fillBuffer(buffer);
    Channel timeDomainResult = audioProcessor.compute(buffer[0]);

    return timeDomainResult;
}