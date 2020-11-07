#include "GraphGui.h"
#include <iostream>

#define TO_KHZ 0.001

namespace SF = Spectrogram::Fourier;
namespace SA = Spectrogram::Audio;
namespace SP = Spectrogram::PNG;

GraphGui::GraphGui(QWidget *parent) :
        QMainWindow(parent),
        audioSystem(std::make_unique<Backend::Soundio>()) {

    // Choose a device
    auto device = audioSystem.devices()[1];
    // when length == sampleRate, a buffer is 1 second long
    // when length == sampleRate / 100, a buffer is 10 milliseconds long
    size_t channelLength = device.sampleRate / 100; 

    // Configure our buffer to hold the amount of data we want
    buffer.resize(device.channelCount);
    for (auto &channel : buffer)
        channel.resize(channelLength);

    // Tell the system to start listening to that device
    audioSystem.start(device, std::chrono::seconds(2));

    // Set up the audio processor, too
    audioProcessor.setSampleSize(channelLength);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // setup customPlot as central widget of window:
    customPlot = new QCustomPlot(this);

    setCentralWidget(customPlot);

    customPlot->xAxis->setLabel("Time (?)");
    customPlot->yAxis->setLabel("Frequency (Hz)");

    yAxisSize = channelLength / 2;
    xAxisSize = 800;

    setupRealTimeColorMap();
    setGeometry(100, 100, 500, 400);

    setupPngWriter();
}

GraphGui::~GraphGui() {
    audioSystem.stop();
    writerThread.quit();
    writerThread.wait();
}

void GraphGui::createColorScale() {
    QCPColorScale *colorScale = new QCPColorScale(customPlot);
    customPlot->plotLayout()->addElement(0, 1, colorScale);
    colorScale->setLabel("dB change from baseline");
    colorMap->setColorScale(colorScale);

    QCPMarginGroup *group = new QCPMarginGroup(customPlot);
    colorScale->setMarginGroup(QCP::msTop | QCP::msBottom, group);
    customPlot->axisRect()->setMarginGroup(QCP::msTop | QCP::msBottom, group);
}

// TODO: Maybe this works right??? Not sure how to test
void GraphGui::setYAxisLog()
{
  /* To change the axis scale type from a linear scale to a logarithmic scale, 
   *  set QCPAxis::setScaleType to QCPAxis::stLogarithmic.
  */
  QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
  customPlot->yAxis->setTicker(logTicker);
  customPlot->yAxis->setScaleType(QCPAxis::stLogarithmic);

  colorMap->setDataScaleType(QCPAxis::stLogarithmic);
  colorMap->colorScale()->axis()->setTicker(logTicker);
  colorMap->colorScale()->setDataScaleType(QCPAxis::stLogarithmic);
}

void GraphGui::setupRealTimeColorMap() {

    // include this section to fully disable antialiasing for higher performance:
    customPlot->setNotAntialiasedElements(QCP::aeAll);
    QFont font;
    font.setStyleStrategy(QFont::NoAntialias);
    customPlot->xAxis->setTickLabelFont(font);

    colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);

    createColorScale();

    //setYAxisLog();

    /* setSize(keysize as in xAxis, valuesize as in yAxis) */
    colorMap->data()->setKeySize(xAxisSize);
    colorMap->data()->setValueSize(yAxisSize);
    colorMap->data()->setRange(QCPRange(0, xAxisSize), QCPRange(0, yAxisSize));

    colorMap->data()->fill(0);
    colorMap->setGradient(QCPColorGradient::gpGrayscale);
    colorMap->rescaleDataRange(true);
    customPlot->rescaleAxes();
    customPlot->replot();

    dataTimer = new QTimer(this);
    // setup a timer that repeatedly calls GraphGui::realtimeColorSlot:
    connect(dataTimer, SIGNAL(timeout()), this, SLOT(realtimeColorSlot()));
    dataTimer->start(0); // Interval 0 means to refresh as fast as possible
}

void GraphGui::setupPngWriter()
{
    pngWriter = new SP::Writer();
    pngWriter->setFileName("snapshot.png");
    pngWriter->moveToThread(&writerThread);

    connect(&writerThread, &QThread::finished, pngWriter, &QObject::deleteLater);
    connect(this, &GraphGui::writePngSnapShot, pngWriter, &SP::Writer::onWritePng);
    connect(pngWriter, &SP::Writer::writingDone, this, &GraphGui::printSuccess);
    connect(colorMap, &QCPColorMap::gradientChanged, pngWriter, &SP::Writer::onGradiantChanged);
    writerThread.start();
}

void GraphGui::realtimeColorSlot() {
    static QTime time(QTime::currentTime());
    static bool picTaken = false;
    // calculate two new data points:
    double key = time.elapsed() / 1000.0; // time elapsed since start, in seconds
    static double lastPointKey = 0;
    SA::Channel newChannel = getNewChannel();
    if (key - lastPointKey > 0.01) // at most re-map every 10 ms
    {
        //std::cout << key << std::endl;
        // make key axis range scroll with the data (at a constant range size of xAxisSize)
        colorMap->data()->setKeyRange(QCPRange(key, key+xAxisSize));
        for (int x = 0; x < xAxisSize; ++x) {
            for (int y = 0; y < yAxisSize; ++y) {
                // put new channel into the last column of the colormap
                if (x == xAxisSize - 1) {
                    // setCell needs to be used if working with logscale
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
        customPlot->rescaleAxes();
        //customPlot->replot();
        lastPointKey = key;
    }
    customPlot->replot();

    if(key > 15 && !picTaken)
    {
        picTaken = true;
        onTakeSnapShotClicked();
    }
}

SA::Channel GraphGui::getNewChannel() {

    audioSystem.fillBuffer(buffer);
    Channel timeDomainResult = audioProcessor.compute(buffer[0]);

    return timeDomainResult;
}

void GraphGui::printSuccess(bool success) {
    QString msg;
    QString fileName = pngWriter->getFileName();
    if(success) {
        msg = QString("%1 saved to present folder.").arg(fileName);
    }
    else {
        msg = QString("Error: %1 not saved."). arg(fileName);
    }
    
    std::cout << msg.toStdString() << std::endl;
}

void GraphGui::onTakeSnapShotClicked() {
    emit writePngSnapShot(colorMap->data());
}
