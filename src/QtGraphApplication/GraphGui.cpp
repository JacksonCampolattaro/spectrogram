#include "GraphGui.h"

#include <Spectrogram/Fourier/Transformer.h>

#define TO_KHZ 0.001


//using namespace Spectrogram;

namespace SF = Spectrogram::Fourier;
namespace SA = Spectrogram::Audio;

GraphGui::GraphGui(QWidget *parent) :
        QMainWindow(parent),
        audioSystem(std::make_unique<Audio::Backend::Soundio>()) {

    // Choose a device
    auto device = audioSystem.devices()[2];
    // when length == sampleRate, a buffer is 1 second long
    // when length == sampleRate / 100, a buffer is 10 milliseconds long
    size_t channelLength = device.sampleRate / 30;

    // Configure our buffer to hold the amount of data we want
    buffer = Audio::Buffer(device, channelLength);

    // Tell the system to start listening to that device
    audioSystem.start(device, std::chrono::seconds(2));

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
}

GraphGui::~GraphGui() {
    audioSystem.stop();
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
void GraphGui::setYAxisLog() {
    /* To change the axis scale type from a linear scale to a logarithmic scale,
     *  set QCPAxis::setScaleType to QCPAxis::stLogarithmic.
    */
    QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
    logTicker->setLogBase(10);
    customPlot->yAxis->setTicker(logTicker);
    customPlot->yAxis->setScaleType(QCPAxis::stLogarithmic);

//    colorMap->colorScale()->axis()->setTicker(logTicker);
//    colorMap->colorScale()->setDataScaleType(QCPAxis::stLogarithmic);
//    colorMap->setDataScaleType(QCPAxis::stLogarithmic);
}

void GraphGui::setupRealTimeColorMap() {

    // include this section to fully disable antialiasing for higher performance:
    customPlot->setNotAntialiasedElements(QCP::aeAll);
    QFont font;
    font.setStyleStrategy(QFont::NoAntialias);
    customPlot->xAxis->setTickLabelFont(font);

    colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);

    createColorScale();

    setYAxisLog();

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

void GraphGui::realtimeColorSlot() {

    audioSystem.fillBuffer(buffer);
    draw(buffer);

    /*
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
     */
}

void GraphGui::draw(const Audio::Buffer &buffer) {
    std::cout << "drawing" << std::endl;

    // Shift everything on the plot to the left
    for (int x = 0; x < xAxisSize - 1; ++x) {
        for (int y = 0; y < yAxisSize; ++y) {

            // Each element is set to the value of the element to the right
            colorMap->data()->setCell(x, y, colorMap->data()->cell(x + 1, y));
        }
    }

    // Get the latest information
    auto frequencyDomainBuffer = Fourier::transform(buffer);

    // Make sure the y axis is scaled correctly
    auto maxFreq = (--frequencyDomainBuffer.end())->first;
    colorMap->data()->setRange(QCPRange(0, xAxisSize),
                               QCPRange(0, maxFreq));

    // Plot the latest data at the rightmost column
    auto iter = frequencyDomainBuffer.begin();
    for (int y = 0; y < yAxisSize; ++y) {

        // Only plot one channel, for now
        auto value = (90.0f + (*iter).second[0]) / 90.0f;
        colorMap->data()->setCell(xAxisSize - 1, y, value);

        iter++;
    }

    // Redraw the plot
    colorMap->rescaleDataRange(true);
    customPlot->rescaleAxes();
    customPlot->replot();
}

