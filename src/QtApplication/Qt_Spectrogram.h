/* \file Qt_Spectrogram.h
 *
 * Course:  ECE 4574
 * Author:  Joshua Lyons
 * Date:    October 10, 2020
 * Revised:	November 1, 2020
 *
 * This is the header file for the Spectrogram GUI class,
 * which isn't the fastest in Qt, but will suffice as a
 * deliverable for the first Sprint of our semester project.
 *
*/

#ifndef QT_SPECTROGRAM_H
#define QT_SPECTROGRAM_H

// TODO: Connect these modules
//#include <Spectrogram/Fourier/processor.h>//"processor.h"
//#include <Spectrogram/Audio/Device.h>

#include <QWidget>
#include <QLayout>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
//#include <QThread>
#include <QDebug>

// Namespace convention for QtCreator IDE Apps
//QT_BEGIN_NAMESPACE
//namespace Ui { class QtSpectrogram; }
//QT_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

// Can change this as needed
//typedef double plotDataType;
typedef qreal plotDataType;

/*! \class QtSpectrogram
\brief [Insert brief summary here]

[Insert longer, more detailed explanation here]
 */
class QtSpectrogram : public QWidget
{
	Q_OBJECT
public:
	/// Construct and initialize a default QtSpectrogram Application
	QtSpectrogram(QWidget *parent = nullptr);
	//~QtSpectrogram() = default;
	
	// API wrapper function for signal passing
	//void sendFreqData(plotDataType data);
	
	/*! [Insert brief API-style usage summary here]
		\param data the data to draw to the plot
	*/
	void updatePlot(plotDataType data);

public slots:
	/// Receives frequency data signal
	void getFreqData(plotDataType data);
	//void updatePlot(plotDataType data);

private:
	//Ui::QtSpectrogram *ui; // Specific to QtCreator IDE Apps
	//QtSpectrogram *ui;
	QChart *m_Chart;
	QChartView *m_View;
	
	// Composite objects
	//Processor *mProcessor;
	//Device *mDevice;
	
	bool isPlotReady; // Status flag to check (but would ideally be a semaphore)
	
	void setupUi();

signals:
	void freqDataPacket(plotDataType data);
};

#endif // QT_SPECTROGRAM_H
