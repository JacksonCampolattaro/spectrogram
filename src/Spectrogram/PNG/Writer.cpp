#include "Writer.h"
#include <iostream>

namespace Spectrogram::PNG
{

    Writer::Writer(QWidget *parent, QCPColorMap *colorMap, QString nFileName) :
            QObject(parent),
            runningMap(colorMap),
            fileName(nFileName) {

        pngPlot = new QCustomPlot();
        pngColorMap = new QCPColorMap(pngPlot->xAxis, pngPlot->yAxis);
    }

    void Writer::setFileName(QString newFileName)
    {
        fileName = newFileName;
    }

    QString Writer::getFileName() {
        return fileName;
    }

    void Writer::setRunningMap(QCPColorMap *colorMap) {
        runningMap = colorMap;
    }

    void Writer::onWriteSnapShot()
    {

        takeSnapShot();
        fixFileName();
        bool success = pngPlot->savePng(fileName);

        emit writingDone(success);
        
    }

    void Writer::takeSnapShot()
    {
        copyRunningMap();
    }

    void Writer::copyRunningMap() {
        pngColorMap->valueAxis()->setScaleType(runningMap->valueAxis()->scaleType());
        pngColorMap->setData(runningMap->data(), true);
        pngColorMap->setGradient(runningMap->gradient());
        pngColorMap->rescaleDataRange(true);
        pngPlot->rescaleAxes();
        pngPlot->replot();
        //pngPlot->axisRect()->setAutoMargins(QCP::msNone);
        //pngPlot->axisRect()->setMargins(QMargins(0,0,0,0));
    }

    void Writer::fixFileName() {
        static int numSnapShots = 1;

        QString fixedFileName = fileName;
        if(numSnapShots == 1 && !fixedFileName.contains(".png", Qt::CaseInsensitive)) {
            fixedFileName.append(QString("_%1.png").arg(numSnapShots));
        }
        else if (numSnapShots == 1){
            fixedFileName.replace(".png", QString("_%1.png").arg(numSnapShots), Qt::CaseInsensitive);
        }
        else {
            fixedFileName.replace(QString("_%1.png").arg(numSnapShots - 1), QString("_%1.png").arg(numSnapShots));
        }
        numSnapShots++;
        fileName = fixedFileName;
    }
}


