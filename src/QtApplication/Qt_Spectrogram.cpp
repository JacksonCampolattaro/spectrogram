/* Qt_Spectrogram.cpp
 *
 * Course:  ECE 4574
 * Author:  Joshua Lyons
 * Date:    October 10, 2020
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

#include <QWidget>
#include <QLayout>
#include <QtCharts/QChart>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

#include <QDebug>
#include <random>

QtSpectrogram::QtSpectrogram(QWidget *parent)
    : QWidget(parent)
    //, ui(new Ui::QtSpectrogram) // Only for Qt Creator IDE
{
	ui = new QtSpectrogram;
	ui->setupUi(parent);//ui->setupUi(this);
	updatePlot(0.0);
}

QtSpectrogram::~QtSpectrogram()
{
    delete ui;
}


void QtSpectrogram::setupUi(QWidget *parent) {
	
	setObjectName("display");

	m_scene = new QGraphicsScene(parent);
	//m_scene->setObjectName("myScene");

	m_view = new QGraphicsView(m_scene, parent);
	//m_view->setObjectName("myView");

	/*** Don't forget this step ***/
	QObject::connect(this, SIGNAL(freqDataPacket(plotDataType)),
    	this, SLOT(getFreqData(plotDataType)));

	m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	m_layout = new QGridLayout();

	m_layout->addWidget(m_view, 0, 0);
	m_view->centerOn(0, 0);
	

	this->setLayout(m_layout);
	//resize(500, 500);
	this->show();
}

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

    mChart = new QChart();
    //int nbins = 20;
    //int npts = 10000;

    qDebug() << data; // Just satisfying the compiler for now
    mChart->setTitle("Sampled Audio Frequency Data Visualizer");
    mChart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    mChart->addAxis(axisX, Qt::AlignBottom);

    int max = 1;
    QValueAxis *axisY = new QValueAxis();

    axisY->setRange(0,max);
    mChart->addAxis(axisY, Qt::AlignLeft);

    mChart->legend()->setVisible(true);
    mChart->legend()->setAlignment(Qt::AlignBottom);
    //ui->chartView->setChart(mChart);
    //ui->chartView->setRenderHint(QPainter::Antialiasing);
    //ui->chartView->update();
	chartView->setChart(mChart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->update();

    // Clean up memory before returning?
    //delete data;
}
