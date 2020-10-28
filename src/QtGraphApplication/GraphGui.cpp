#include "GraphGui.h"

GraphGui::GraphGui(QWidget *parent) :
	QMainWindow(parent)
{
	// setup customPlot as central widget of window:
	QCustomPlot *customPlot = new QCustomPlot(this);
	
	setCentralWidget(customPlot);

	QCPColorMap *colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);\

	colorMap->data()->setSize(50, 50);
  	colorMap->data()->setRange(QCPRange(0, 2), QCPRange(0, 2));
  	for (int x=0; x<50; ++x)
    	for (int y=0; y<50; ++y)
      		colorMap->data()->setCell(x, y, qCos(x/10.0)+qSin(y/10.0));
  	colorMap->setGradient(QCPColorGradient::gpPolar);
  	colorMap->rescaleDataRange(true);
  	customPlot->rescaleAxes();
  	customPlot->replot();

	setGeometry(100, 100, 500, 400);
}

