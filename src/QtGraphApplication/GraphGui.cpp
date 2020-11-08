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
    customPlot->axisRect()->setupFullAxesBox(true);
    setCentralWidget(customPlot);
    setGeometry(100, 200, 800, 400);

    setupPlot(800, 2205);

    //colorMap->data()->setRange({0, (float) xAxisSize}, {0, 2205});
    colorMap->data()->setRange({-4, 4}, {-4, 4});
    customPlot->rescaleAxes();

    double x, y, z;
    for (int xIndex = 0; xIndex < xAxisSize; ++xIndex) {
        for (int yIndex = 0; yIndex < yAxisSize; ++yIndex) {
            colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
            double r = 3 * qSqrt(x * x + y * y) + 1e-2;
            z = 2 * x * (qCos(r + 2) / r -
                         qSin(r + 2) / r); // the B field strength of dipole radiation (modulo physical constants)
            colorMap->data()->setCell(xIndex, yIndex, z);
        }
    }
    colorMap->rescaleDataRange();

    //auto colorScale = new QCPColorScale(customPlot);

//    colorMap->setGradient(QCPColorGradient::gpJet);
//    colorMap->rescaleDataRange(true);

//
//    customPlot->xAxis->setLabel("Time (?)");
//    customPlot->yAxis->setLabel("Frequency (Hz)");
//
}

void GraphGui::createColorScale() {
//    QCPColorScale *colorScale = new QCPColorScale(customPlot);
//    customPlot->plotLayout()->addElement(0, 1, colorScale);
//    colorScale->setLabel("dB change from baseline");
//    colorMap->setColorScale(colorScale);
//
//    QCPMarginGroup *group = new QCPMarginGroup(customPlot);
//    colorScale->setMarginGroup(QCP::msTop | QCP::msBottom, group);
//    customPlot->axisRect()->setMarginGroup(QCP::msTop | QCP::msBottom, group);
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

    // Get the latest information
    auto frequencyDomainBuffer = Fourier::transform(buffer);

    // Make sure the graph is scaled correctly for the data being drawn
//    if (yAxisSize != buffer.numFrames() / 2) {
//
//        setupPlot(xAxisSize, buffer.numFrames() / 2);
//
//        // Make sure the y axis is scaled correctly
//        auto maxFreq = (--frequencyDomainBuffer.end())->first;
//        colorMap->data()->setRange(QCPRange(0, xAxisSize),
//                                   QCPRange(0, maxFreq));
//    }

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
    //customPlot->rescaleAxes();
    colorMap->rescaleDataRange();
    customPlot->replot();
}

void GraphGui::setupPlot(size_t xSize, size_t ySize) {

//    std::cout << "Setting up the plot" << std::endl;

    yAxisSize = ySize;
    xAxisSize = xSize;

    colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
    colorMap->data()->setSize(xAxisSize, 2205);

    auto colorScale = new QCPColorScale(customPlot);
    customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    colorScale->setType(
            QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale
    colorScale->axis()->setLabel("Magnetic Field Strength");

    colorMap->setGradient(QCPColorGradient::gpPolar);

    auto marginGroup = new QCPMarginGroup(customPlot);
    customPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
}

