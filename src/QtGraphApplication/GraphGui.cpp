#include "GraphGui.h"

#include <Spectrogram/Fourier/Transformer.h>

#define TO_KHZ 0.001


//using namespace Spectrogram;

namespace SF = Spectrogram::Fourier;
namespace SA = Spectrogram::Audio;

GraphGui::GraphGui(QWidget *parent) :
        QMainWindow(parent) {

    // Set the dimensions of this window
    setGeometry(100, 100, 1500, 700);

    // Create a plot widget and add it to the window
    customPlot = new QCustomPlot(this);
    setCentralWidget(customPlot);

    // Create a colorMap
    colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);

    // Create a color scale
    auto colorScale = new QCPColorScale(customPlot);

    customPlot->xAxis->setLabel("Time (s)");
    customPlot->yAxis->setLabel("Frequency (Hz)");

    colorScale->axis()->setLabel("Intensity (unit?)");
    customPlot->plotLayout()->addElement(0, 1, colorScale);
    colorMap->setColorScale(colorScale);

    colorMap->valueAxis()->setScaleType(QCPAxis::stLogarithmic);
    QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
    logTicker->setLogBase(2);
    colorMap->valueAxis()->setTicker(logTicker);

    colorMap->setGradient(QCPColorGradient::gpGrayscale);
    colorMap->setInterpolate(true);

    auto marginGroup = new QCPMarginGroup(customPlot);
    customPlot->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);

    colorMap->data()->setSize(xAxisSize, yAxisSize);
}

void GraphGui::draw(const Audio::Buffer &buffer) {

    // Calculate the latest buffer value
    auto frequencyDomainBuffer = Fourier::transform(buffer);

    // Make sure the graph is scaled correctly for the data being drawn
    if (colorMap->data()->valueRange().upper != frequencyDomainBuffer.maxFrequency()) {

        // Make sure the y axis is scaled correctly
        auto oldestTime = (float) colorMap->data()->keySize() * frequencyDomainBuffer.time();
        colorMap->data()->setRange(QCPRange(-oldestTime, 0),
                                   QCPRange(35, frequencyDomainBuffer.maxFrequency()));

        // Update the axes to show the new range
        customPlot->rescaleAxes();
    }

    // Move all existing data to the left
    shiftData();

    // Add another column
    addData(frequencyDomainBuffer);

    // Redraw the plot
    colorMap->rescaleDataRange();
    customPlot->replot();
}

void GraphGui::shiftData() {

    // Shift everything on the plot to the left
    for (int x = 0; x < colorMap->data()->keySize() - 1; ++x) {
        for (int y = 0; y < colorMap->data()->valueSize(); ++y) {

            // Each element is set to the value of the element to the right
            colorMap->data()->setCell(x, y, colorMap->data()->cell(x + 1, y));
        }
    }

}

void GraphGui::addData(const Fourier::FrequencyDomainBuffer &frequencyDomainBuffer) {

    // Plot the latest data at the rightmost column
    for (int y = 0; y < colorMap->data()->valueSize(); ++y) {

        double key, value;
        colorMap->data()->cellToCoord(xAxisSize - 1, y, &key, &value);

        // Equation found here: https://stackoverflow.com/questions/19472747/convert-linear-scale-to-logarithmic
        auto max = colorMap->valueAxis()->range().upper;
        auto min = colorMap->valueAxis()->range().lower;
        value = pow(2, ((value - min) / (max - min)) * (log2(max) - log2(min)) + log2(min));

        // Only plot one channel, for now
        auto intensity = (90.0f + frequencyDomainBuffer.at(value)[0]) / 90.0f;
        colorMap->data()->setCell(xAxisSize - 1, y, intensity);

    }

}

