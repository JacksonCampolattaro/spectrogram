/* Qt_Spectrogram.h
 *
 * Course:  ECE 4574
 * Author:  Joshua Lyons
 * Date:    October 10, 2020
 *
 * This is the header file for the Spectrogram GUI class,
 * which isn't the fastest in Qt, but will suffice as a
 * deliverable for the first Sprint of our semester project.
 *
*/

#ifndef QT_SPECTROGRAM_H
#define QT_SPECTROGRAM_H

// TODO: Connect these modules
//#include "processor.h"
//#include "Device.h"

#include <QWidget>
#include <QtCharts/QChart>

// Namespace convention for QtCreator IDE Apps
QT_BEGIN_NAMESPACE
namespace Ui { class QtSpectrogram; }
QT_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

// Can change this as needed
typedef double plotDataType;

class QtSpectrogram : public QWidget
{
    Q_OBJECT

public:
    QtSpectrogram(QWidget *parent = nullptr);
    ~QtSpectrogram();

    // API wrapper function for signal passing
     void sendFreqData(plotDataType data);

private slots:
    void getFreqData(plotDataType data);
    void updatePlot(plotDataType data);

private:
    Ui::QtSpectrogram *ui; // Specific to QtCreator IDE Apps
    QChart *mChart;
    //Processor *mProcessor;
    //Device *mDevice;
    bool isPlotReady; // Status flag to check (but would ideally be a semaphore)

signals:
    void freqDataPacket(plotDataType data);
};

#endif // QT_SPECTROGRAM_H
