#include "GraphGui.h"

#include <Spectrogram/Fourier/Transformer.h>

#define TO_KHZ 0.001


//using namespace Spectrogram;

namespace SF = Spectrogram::Fourier;
namespace SA = Spectrogram::Audio;

GraphGui::GraphGui(QWidget *parent) :
        QMainWindow(parent) {

    // Set the dimensions of this window
    setGeometry(100, 100, 800, 800);

    // Create a plot widget and add it to the window
    customPlot = new QCustomPlot(this);
    setCentralWidget(customPlot);

    // Create a colorMap
    colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);

    customPlot->xAxis->setLabel("Time");
    customPlot->yAxis->setLabel("Frequency (Hz)");

    auto colorScale = new QCPColorScale(customPlot);
    colorScale->axis()->setLabel("Intensity (unit?)");
    customPlot->plotLayout()->addElement(0, 1, colorScale);
    colorMap->setColorScale(colorScale);

    colorMap->valueAxis()->setScaleType(QCPAxis::stLogarithmic);
    QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
    logTicker->setLogBase(10);
    colorMap->valueAxis()->setTicker(logTicker);

    colorMap->setGradient(QCPColorGradient::gpGrayscale);
    colorMap->setInterpolate(true);

    auto marginGroup = new QCPMarginGroup(customPlot);
    customPlot->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
}

void GraphGui::draw(const Audio::Buffer &buffer) {

    // Get the latest information
    auto frequencyDomainBuffer = Fourier::transform(buffer);

    // Make sure the graph is scaled correctly for the data being drawn
    if (colorMap->data()->valueRange().upper != frequencyDomainBuffer.maxFrequency()) {

        colorMap->data()->setSize(xAxisSize, yAxisSize);

        // Make sure the y axis is scaled correctly
        auto maxFreq = frequencyDomainBuffer.maxFrequency();
        std::cout << maxFreq << std::endl;
        colorMap->data()->setRange(QCPRange(-(float) xAxisSize, 0),
                                   QCPRange(30, maxFreq));
        customPlot->rescaleAxes();
    }

    // Shift everything on the plot to the left
    for (int x = 0; x < colorMap->data()->keySize() - 1; ++x) {
        for (int y = 0; y < colorMap->data()->valueSize(); ++y) {

            // Each element is set to the value of the element to the right
            colorMap->data()->setCell(x, y, colorMap->data()->cell(x + 1, y));
        }
    }

    // Plot the latest data at the rightmost column
    for (int y = 0; y < colorMap->data()->valueSize(); ++y) {

        double key, value;
        colorMap->data()->cellToCoord(xAxisSize - 1, y, &key, &value);

        // Equation found here: https://stackoverflow.com/questions/19472747/convert-linear-scale-to-logarithmic
        auto max = colorMap->valueAxis()->range().upper;
        auto min = colorMap->valueAxis()->range().lower;
        value = pow(10, ((value - min)/(max - min)) * (log10(max) - log10(min)) + log10(min));

        // Only plot one channel, for now
        auto intensity = (90.0f + frequencyDomainBuffer.at(value)[0]) / 90.0f;
        colorMap->data()->setCell(xAxisSize - 1, y, intensity);

    }

    // Redraw the plot
    colorMap->rescaleDataRange();
    customPlot->replot();
}

