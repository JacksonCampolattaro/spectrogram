#ifndef GRAPH_GUI_H
#define GRAPH_GUI_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QTimer>
#include <Spectrogram/Audio/Buffer.h>

class GraphGui : public QMainWindow
{
	Q_OBJECT

public:
	explicit GraphGui(QWidget *parent = 0);

	//void setYAxisLog();
	void setupRealTimeColorMap();

public slots:
	void realtimeColorSlot();

private:
	void createColorScale();
	Spectrogram::Audio::Channel getFakeChannel();


	QCustomPlot *customPlot;
	QCPColorMap *colorMap;

	int yAxisSize;
	int xAxisSize;
	QTimer *dataTimer;

};

#endif // GRAPH_GUI_H