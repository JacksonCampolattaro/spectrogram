#include "QtSpectrogram.h"

#include <Spectrogram/Fourier/Transformer.h>

//using namespace Spectrogram;

QtSpectrogram::QtSpectrogram(QWidget *parent) :
        QCustomPlot(parent) {

    // Create a colorMap
    colorMap = new QCPColorMap(this->xAxis, this->yAxis);

    // Create a color scale
    auto colorScale = new QCPColorScale(this);

    this->xAxis->setLabel("Time (s)");
    this->yAxis->setLabel("Frequency (Hz)");

    colorScale->axis()->setLabel("Intensity (unit?)");
    this->plotLayout()->addElement(0, 1, colorScale);
    colorMap->setColorScale(colorScale);

    colorMap->valueAxis()->setScaleType(QCPAxis::stLogarithmic);
    QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
    logTicker->setLogBase(2);
    colorMap->valueAxis()->setTicker(logTicker);

    colorMap->setGradient(QCPColorGradient::gpHot);
    colorMap->setInterpolate(true);

    auto marginGroup = new QCPMarginGroup(this);
    this->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);

    colorMap->data()->setSize(xAxisSize, yAxisSize);

    // Should happen after creating the colormap
    setupPngWriter();
}

QtSpectrogram::~QtSpectrogram() {
    writerThread.quit();
    writerThread.wait();
}

void QtSpectrogram::draw(const Audio::Buffer &buffer) {

    // Calculate the latest buffer value
    auto frequencyDomainBuffer = Fourier::transform(buffer);

    // Make sure the graph is scaled correctly for the data being drawn
    if (colorMap->data()->valueRange().upper != frequencyDomainBuffer.maxFrequency()) {

        // Make sure the y axis is scaled correctly
        auto oldestTime = (float) colorMap->data()->keySize() * frequencyDomainBuffer.time();
        colorMap->data()->setRange(QCPRange(-oldestTime, 0),
                                   QCPRange(35, frequencyDomainBuffer.maxFrequency()));

        // Update the axes to show the new range
        this->rescaleAxes();
    }

    // Move all existing data to the left
    shiftData();

    // Add another column
    addData(frequencyDomainBuffer);

    // Redraw the plot
    colorMap->rescaleDataRange();
    this->replot();
}

void QtSpectrogram::shiftData() {

    // Shift everything on the plot to the left
    for (int x = 0; x < colorMap->data()->keySize() - 1; ++x) {
        for (int y = 0; y < colorMap->data()->valueSize(); ++y) {

            // Each element is set to the value of the element to the right
            colorMap->data()->setCell(x, y, colorMap->data()->cell(x + 1, y));
        }
    }

}

void QtSpectrogram::addData(const Fourier::FrequencyDomainBuffer &frequencyDomainBuffer) {

    // Plot the latest data at the rightmost column
    for (int y = 0; y < colorMap->data()->valueSize(); ++y) {

        double key, value;
        colorMap->data()->cellToCoord(xAxisSize - 1, y, &key, &value);

        // Equation found here: https://stackoverflow.com/questions/19472747/convert-linear-scale-to-logarithmic
        auto max = colorMap->valueAxis()->range().upper;
        auto min = colorMap->valueAxis()->range().lower;
        value = pow(2, ((value - min) / (max - min)) * (log2(max) - log2(min)) + log2(min));

        // Only plot one channel, for now
        float intensity = 0;
        for (const auto &channel : frequencyDomainBuffer.at(value))
            intensity += (90.0f + channel) / 90.0f;
        intensity = intensity / frequencyDomainBuffer.numChannels();

        colorMap->data()->setCell(xAxisSize - 1, y, intensity);

    }

}

// Needs to be in it's own thread so that when it's updated to save 
// continuously it wont interfere with gui when it does computationally 
// expensive picture appending.
void QtSpectrogram::setupPngWriter()
{
    pngWriter = new Spectrogram::PNG::Writer();
    pngWriter->setFileName("snapshot.png");
	// pngWriter will never modify the spectrogram's colorMap, 
	// it just needs it to copy its data periodically
	pngWriter->setRunningMap(colorMap);
    pngWriter->moveToThread(&writerThread);

    connect(&writerThread, &QThread::finished, pngWriter, &QObject::deleteLater);
    connect(this, &QtSpectrogram::writeSnapShot, pngWriter, &Spectrogram::PNG::Writer::onWriteSnapShot);
    connect(pngWriter, &Spectrogram::PNG::Writer::writingDone, this, &QtSpectrogram::onWritingDone);
    
    writerThread.start();
}
void QtSpectrogram::saveSnapShotPressed() {
    emit writeSnapShot();
}
void QtSpectrogram::onWritingDone(bool success) {
    QString filename = pngWriter->getFileName();
    emit snapShotWritingDone(success, filename);
}