#include "GraphGui.h"

#include <Spectrogram/Fourier/Transformer.h>

#define TO_KHZ 0.001


//using namespace Spectrogram;

namespace SF = Spectrogram::Fourier;
namespace SA = Spectrogram::Audio;

GraphGui::GraphGui(QWidget *parent) :
        QMainWindow(parent) {

    // setup customPlot as central widget of window:
    customPlot = new QCustomPlot(this);

    setCentralWidget(customPlot);
//
//    customPlot->xAxis->setLabel("Time (?)");
//    customPlot->yAxis->setLabel("Frequency (Hz)");
//
//    //yAxisSize = channelLength / 2;
//    xAxisSize = 800;

    setGeometry(100, 200, 800, 400);
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
//
//    // include this section to fully disable antialiasing for higher performance:
//    customPlot->setNotAntialiasedElements(QCP::aeAll);
//    QFont font;
//    font.setStyleStrategy(QFont::NoAntialias);
//    customPlot->xAxis->setTickLabelFont(font);
//
//    colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
//
//    createColorScale();
//
//    setYAxisLog();
//
//    /* setSize(keysize as in xAxis, valuesize as in yAxis) */
//    colorMap->data()->setKeySize(xAxisSize);
//    colorMap->data()->setValueSize(yAxisSize);
//    colorMap->data()->setRange(QCPRange(0, xAxisSize), QCPRange(0, yAxisSize));
//
//    colorMap->data()->fill(0);
//    colorMap->setGradient(QCPColorGradient::gpGrayscale);
//    colorMap->rescaleDataRange(true);
//    customPlot->rescaleAxes();
//    customPlot->replot();
}

void GraphGui::draw(const Audio::Buffer &buffer) {

    // Make sure the graph is scaled correctly for the data being drawn
    if (yAxisSize != buffer.numFrames() / 2) {
        std::cout << "changing" << std::endl;
        setupPlot(800, buffer.numFrames() / 2);
    }

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
    customPlot->rescaleAxes();
    customPlot->replot();
}

void GraphGui::setupPlot(size_t xSize, size_t ySize) {

}

