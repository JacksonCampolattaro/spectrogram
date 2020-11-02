/* Qt_Spectrogram.cpp
 *
 * Course:  ECE 4574
 * Author:  Joshua Lyons
 * Date:    October 10, 2020
 * Revised:	November 1, 2020
 *
 * This is the Qt GUI implementation file for our Sprint
 * deliverable, which displays the processed results of
 * the other modules (they do most of the heavy lifting).
 *
 * We plan to heavily modify/replace this suboptimally
 * performing Qt implementation in future Sprints, with
 * a more efficient OpenGL library.
 *
*/

#include "Qt_Spectrogram.h"
//#include "ui_Qt_Spectrogram.h" // Only for Qt Creator IDE

#include <QCore>
#include <QWidget>
#include <QLayout>
#include <QString>
#include <QDebug>
#include <QLabel>
#include <QtCharts/QChart>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <random>
#include <exception>
#include <stdexcept>

// This can be changed to a better convention later, I just used it for quick testing
#define NUM_BINS 20
#define NUM_SAMPLES 100
#define Y_AXIS_RANGE 60

QtSpectrogram::QtSpectrogram(QWidget *parent)
    : QWidget(parent)
    //, ui(new Ui::QtSpectrogram) // Only for Qt Creator IDE
{
	//ui = new QtSpectrogram;
	//ui->setupUi(this);//ui->setupUi(parent);
	setupUi();
	//updatePlot(0.0);
}

// QtSpectrogram::~QtSpectrogram()
// {
//     delete ui;
// }

//=======================================================================
// Helper functions
//=======================================================================
// Creates dummy data to test GUI with before integrating the other modules
//QVector<plotDataType>* createData(int num) {
QVector<qreal>* createData(int num) {

	//QVector<plotDataType> *data = new QVector<plotDataType>;
	QVector<qreal> *data = new QVector<qreal>;
	std::default_random_engine generator;

	//std::normal_distribution<double> distribution(10.0, 2.0);
	std::uniform_real_distribution<plotDataType> distribution(0.0, Y_AXIS_RANGE);

	// params are arbitrarily chosen
	for(int incr = 0; incr < num; incr++) {
		data->push_front(distribution(generator));
	}
	qDebug() << data;
	return data;
}

// calculate the min value in each bin - find data max and min and divide range into nbins equal bits
QList<qreal>* getBinMins(QVector<qreal> *data, int bins)
{
	qreal min = *std::min_element(data->constBegin(), data->constEnd());
	qreal max = *std::max_element(data->constBegin(), data->constEnd());
	qreal wid = (max - min) / bins;
	QList<qreal> *binMins = new QList<qreal>;
	for (int b = 0; b < bins; b++)
		binMins->append(min + (b + 1)*wid);

	qDebug() << binMins;
	return binMins;
}

// fill a QList with the data counts in each bin
QList<qreal>* calcHist(QVector<qreal> *data, int bins)
{
	QVector<int> H(bins, 0);
	QList<qreal> *binMins = getBinMins(data, bins);

	for (int incr = 0; incr < data->size(); incr++) {
		for (int b = 0; b < bins; b++) {
			if (data->at(incr) <= binMins->at(b)){
				H[b]++;
				break;
			}
		}
	}
	QList<qreal> *hist = new QList<qreal>;
	for (int b = 0; b < bins; b++) {
		hist->append(H[b]);
	}
	qDebug() << hist;
	return hist;
}
//=======================================================================

void QtSpectrogram::setupUi() {

	m_Chart = new QChart();
	//m_Chart->setParent(this);
	m_Chart->setObjectName("dataModel"); // Used for integration testing

	m_View = new QChartView(m_Chart);
	//m_View->setParent(this);
	//m_Chart->setParent(m_View);
	m_View->setObjectName("dataDisplay"); // Used for integration testing
	m_View->setChart(m_Chart); // Last step?
	//m_View->setGeometry(QRect(10, 10, 490, 490));

	m_View->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_View->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	//m_layout = new QGridLayout();
	resize(500, 500);

	//m_View->centerOn(0, 0);
	m_View->fitInView(m_Chart);

	m_View->update();

	/*** Don't forget this step ***/
	QObject::connect(this, SIGNAL(freqDataPacket(plotDataType)),
		this, SLOT(getFreqData(plotDataType)));
	

	/*** End of boilerplate code ***/

	int nbins = NUM_BINS;
	int npts = NUM_SAMPLES;

	// Create a data array and fill it randomly
	QVector<qreal> *data = createData(npts); /// TODO: Connect other modules here

	// Compile its histogram
	QList<qreal> *dataList = calcHist(data, nbins);

	// Define a bar chart of the histogram
	QBarSet *mainSet = new QBarSet("Data");
	mainSet->append(*dataList);

	// the bar chart displays a data series
	QBarSeries *series = new QBarSeries();
	series->append(mainSet);

	// it's part of a QChart for displaying
	m_Chart->addSeries(series);
	m_Chart->setTitle("Sampled Audio Frequency Data Visualizer");
	m_Chart->setAnimationOptions(QChart::SeriesAnimations);

	// set X and Y axes appropriately (max and labels)
	QStringList categories;
	QList<qreal> *binMins = getBinMins(data, nbins);
	for (int incr = 0; incr < nbins; incr++){
		categories << QString("%1 ").arg(binMins->at(incr));
	}

	QBarCategoryAxis *axisX = new QBarCategoryAxis();
	axisX->append(categories);
	//axisX->setLabelsAngle(270);
	m_Chart->addAxis(axisX, Qt::AlignBottom);
	series->attachAxis(axisX);

	int max = Y_AXIS_RANGE;// *std::max_element(dataList->constBegin(), dataList->constEnd());
	QValueAxis *axisY = new QValueAxis();
	//axisY->setRange(0, max);
	axisY->setRange(0, max);// -max, 0);
	m_Chart->addAxis(axisY, Qt::AlignRight);
	series->attachAxis(axisY);

	// overall chart setup
	m_Chart->legend()->setVisible(true);
	m_Chart->legend()->setAlignment(Qt::AlignBottom);
	m_View->setChart(m_Chart);
	m_View->setRenderHint(QPainter::Antialiasing);

	try{ // TODO: Figure out what's causing it to crash each time it tries to update
		m_View->update();
	}
	catch(const std::runtime_error & ex){
		std::cerr << ex.what() << std::endl;
	}
	
	// Clean up memory before returning
	delete data;
	delete dataList;
	delete mainSet;
	delete binMins;
}
//=======================================================================

/*
void QtSpectrogram::sendFreqData(plotDataType data){
    emit freqDataPacket(data);
}
*/

void QtSpectrogram::getFreqData(plotDataType data)
{
    // TODO: Finish this
    if(isPlotReady){
        updatePlot(data);
    }
    else{
        // Cache data
    }
}


void QtSpectrogram::updatePlot(plotDataType data)
{
    // TODO: Add ability to draw bars from data

    // *********************************************************************************
    //TODO: This is what broke it, you cannot make a "new QChart" or "new" anything
    //      everytime you want to update the plot, moved all non-update stuff to constructor
		
	qDebug() << data;
    m_View->update();
}
