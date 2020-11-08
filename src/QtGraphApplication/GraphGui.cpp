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
    customPlot->xAxis->setLabel("Time");
    customPlot->yAxis->setLabel("Frequency (Hz)");
    setCentralWidget(customPlot);
    setGeometry(100, 200, 800, 400);
}

// TODO: Maybe this works right??? Not sure how to test
void GraphGui::setYAxisLog() {
    /* To change the axis scale type from a linear scale to a logarithmic scale,
     *  set QCPAxis::setScaleType to QCPAxis::stLogarithmic.
    */
//    QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
//    logTicker->setLogBase(10);
//    customPlot->yAxis->setTicker(logTicker);
//    customPlot->yAxis->setScaleType(QCPAxis::stLogarithmic);

//    colorMap->colorScale()->axis()->setTicker(logTicker);
//    colorMap->colorScale()->setDataScaleType(QCPAxis::stLogarithmic);
//    colorMap->setDataScaleType(QCPAxis::stLogarithmic);
}

void GraphGui::draw(const Audio::Buffer &buffer) {

    // Get the latest information
    auto frequencyDomainBuffer = Fourier::transform(buffer);

    // Make sure the graph is scaled correctly for the data being drawn
    if (yAxisSize != frequencyDomainBuffer.size()) {
        std::cout << "Setting up " << frequencyDomainBuffer.size() << std::endl;

        setupPlot(200, frequencyDomainBuffer.size());

        // Make sure the y axis is scaled correctly
        auto maxFreq = (--frequencyDomainBuffer.end())->first;
        colorMap->data()->setRange(QCPRange(-(float) xAxisSize, 0),
                                   QCPRange(0, maxFreq));
        customPlot->rescaleAxes();
    }

    // Shift everything on the plot to the left
    for (int x = 0; x < xAxisSize - 1; ++x) {
        for (int y = 0; y < yAxisSize; ++y) {

            // Each element is set to the value of the element to the right
            colorMap->data()->setCell(x, y, colorMap->data()->cell(x + 1, y));
        }
    }

    // Plot the latest data at the rightmost column
    auto iter = frequencyDomainBuffer.begin();
    for (int y = 0; y < yAxisSize; ++y) {

        // Only plot one channel, for now
        auto value = (90.0f + (*iter).second[0]) / 90.0f;
        //std::cout << value << ", ";
        colorMap->data()->setCell(xAxisSize - 1, y, value);

        iter++;
    }
    //std::cout << std::endl;

    // Redraw the plot
    colorMap->rescaleDataRange();
    customPlot->replot();
}

void GraphGui::setupPlot(size_t xSize, size_t ySize) {

//    std::cout << "Setting up the plot" << std::endl;

    yAxisSize = ySize;
    xAxisSize = xSize;

    colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
    colorMap->data()->setSize(xAxisSize, yAxisSize);

    auto colorScale = new QCPColorScale(customPlot);
    customPlot->plotLayout()->addElement(0, 1, colorScale);
    colorMap->setColorScale(colorScale);
    colorScale->axis()->setLabel("Intensity (unit?)");

    colorMap->setGradient(QCPColorGradient::gpPolar);

    auto marginGroup = new QCPMarginGroup(customPlot);
    customPlot->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
}

