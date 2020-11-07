#include "Writer.h"

namespace Spectrogram::PNG
{

    Writer::Writer(QWidget *parent, QString nFileName) :
            QObject(parent),
            fileName(nFileName){

        pngPlot = new QCustomPlot();
        pngColorMap = new QCPColorMap(pngPlot->xAxis, pngPlot->yAxis);
        pngColorMap->setGradient(QCPColorGradient::gpGrayscale);
    }

    void Writer::setFileName(QString newFileName)
    {
        fileName = newFileName;
    }

    QString Writer::getFileName() {
        return fileName;
    }

    void Writer::onWritePng(QCPColorMapData *data)
    {
        static int snapShotsTaken = 1;

        fixFileName(snapShotsTaken);

        takeSnapShot(data);
        bool success = pngPlot->savePng(fileName);

        emit writingDone(success);
        
        snapShotsTaken++;
    }

    void Writer::takeSnapShot(QCPColorMapData *data)
    {
        pngColorMap->setData(data, true);
        pngColorMap->rescaleDataRange(true);
        pngPlot->rescaleAxes();
        pngPlot->replot();
    }

    void Writer::onGradiantChanged(const QCPColorGradient &newGradient)
    {
        pngColorMap->setGradient(newGradient);
    }

    void Writer::fixFileName(const int &incr) {
        if(fileName.contains(".png", Qt::CaseInsensitive)) {
            fileName.replace(".png", QString("_%1.png").arg(incr), Qt::CaseInsensitive);
        }
        else {
            fileName.append(QString("_%1.png").arg(incr));
        }
    }
}


