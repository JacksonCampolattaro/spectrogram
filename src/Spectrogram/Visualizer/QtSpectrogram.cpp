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

    colorScale->axis()->setLabel("Intensity");
    this->plotLayout()->addElement(0, 1, colorScale);
    colorMap->setColorScale(colorScale);

    // Log scale set by default
    setupYAxisLogScale();
    logScale = true;

    changeColorGradient(1);
    colorMap->setInterpolate(true);

    auto marginGroup = new QCPMarginGroup(this);
    this->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);

    colorMap->data()->setSize(xAxisSize, yAxisSize);

    //Initially set data range to 0-1, it will refine the range as it gathers more data
    colorMap->setDataRange(QCPRange(0,1));	

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
                                   QCPRange(minYValue, frequencyDomainBuffer.maxFrequency()));

        // Update the axes to show the new range
        this->rescaleAxes();
    }

    // Move all existing data to the left
    shiftData();

    // Add another column
    addData(frequencyDomainBuffer);

    // Only draw every nth frame
    // static int frameCount = 0;
    // frameCount++;
    // if (frameCount % 1 == 0) {

    // Redraw the plot
    colorMap->rescaleDataRange();
    this->replot();
    // }
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

        float intensity = getIntensity(y, frequencyDomainBuffer);

        colorMap->data()->setCell(xAxisSize - 1, y, intensity);
    }
    emit updateSave();
}

float QtSpectrogram::getIntensity(const int &y, const Fourier::FrequencyDomainBuffer &frequencyDomainBuffer) {
    double value;

    // if logscale get logarithmic y value, else it is linear scale no need to change y
    value = (logScale) ? getLogValue(y) : y;

    // Only plot one channel, for now
    float intensity = 0;
    for (const auto &channel : frequencyDomainBuffer.at(value))
        intensity += (90.0f + channel) / 90.0f;

    return intensity / frequencyDomainBuffer.numChannels();
}

double QtSpectrogram::getLogValue(const int &y) {

    double key, value;
    colorMap->data()->cellToCoord(xAxisSize - 1, y, &key, &value);

    // Equation found here: https://stackoverflow.com/questions/19472747/convert-linear-scale-to-logarithmic
    auto max = colorMap->valueAxis()->range().upper;
    auto min = colorMap->valueAxis()->range().lower;
    return pow(2, ((value - min) / (max - min)) * (log2(max) - log2(min)) + log2(min));
}

void QtSpectrogram::setupYAxisLogScale() {
    minYValue = 30;
    colorMap->valueAxis()->setScaleType(QCPAxis::stLogarithmic);
    QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
    logTicker->setLogBase(2);
    colorMap->valueAxis()->setTicker(logTicker);
}

void QtSpectrogram::setupYAxisLinearScale() {
    minYValue = 0;
    colorMap->valueAxis()->setScaleType(QCPAxis::stLinear);
    QSharedPointer<QCPAxisTicker> linearTicker(new QCPAxisTicker);
    colorMap->valueAxis()->setTicker(linearTicker);
}

void  QtSpectrogram::changeYScaleType(bool log) {
    logScale = log;

    logScale ? setupYAxisLogScale() : setupYAxisLinearScale();
}

void QtSpectrogram::changeColorGradient(int grad) {
    /* enums: 0 - 11
       gpGrayscale 	
       gpHot 	
       gpCold 	
       gpNight 	
       gpCandy 	
       gpGeography 	
       gpIon 	
       gpThermal 	
       gpPolar 	
       gpSpectrum 	
       gpJet 
       gpHues
    */
    QCPColorGradient newColor = static_cast<QCPColorGradient::GradientPreset>(grad);
    colorMap->setGradient(newColor);
}

// Needs to be in it's own thread so that when it saves
// continuously it wont interfere with gui when it does computationally 
// expensive picture appending.
void QtSpectrogram::setupPngWriter() {
    pngWriter = new Spectrogram::PNG::Writer();
    pngWriter->setFileName("spectrogram.png");
	// pngWriter will never modify the spectrogram's colorMap, 
	// it just needs it to copy its data periodically
	pngWriter->setRunningMap(colorMap);
    pngWriter->moveToThread(&writerThread);

    connect(&writerThread, &QThread::finished, pngWriter, &QObject::deleteLater);
    connect(pngWriter, &Spectrogram::PNG::Writer::writingDone, this, &QtSpectrogram::onWritingDone);
    
    connect(this, &QtSpectrogram::startSaving, pngWriter, &Spectrogram::PNG::Writer::onStartSaving);
    connect(this, &QtSpectrogram::stopSaving, pngWriter, &Spectrogram::PNG::Writer::onStopSaving);
    connect(this, &QtSpectrogram::updateSave, pngWriter, &Spectrogram::PNG::Writer::continuousSave);

    writerThread.start();
}

void QtSpectrogram::onWritingDone(bool success) {
    QString filename = pngWriter->getFileName();
    emit pngWritingDone(success, filename);
}

void QtSpectrogram::startSavePressed() {
    emit startSaving();
}

void QtSpectrogram::stopSavePressed() {
    emit stopSaving();
}