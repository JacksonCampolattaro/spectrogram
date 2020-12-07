#include "Writer.h"

namespace Spectrogram::PNG
{

    Writer::Writer(QWidget *parent, QCPColorMap *colorMap, QString nFileName) :
            QObject(parent),
            runningMap(colorMap),
            fileName(nFileName),
            saving(false),
            imageXSize(0),
            runningXSize(0),
            runningYSize (0) {

        pngPlot = new QCustomPlot();
        pngColorMap = new QCPColorMap(pngPlot->xAxis, pngPlot->yAxis);
    }

    Writer::~Writer() {
        cleanupPixVector();
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

    void Writer::onStartSaving() {
        runningXSize = runningMap->data()->keySize();
        runningYSize = runningMap->data()->valueSize();
        imageXSize = 0;

        saving = true;
    }

    void Writer::onStopSaving() {
        saving = false;
        finishSaving();
    }

    void Writer::takeRunningSnapShot() {

        copyRunningMap();

        QPixmap *pxmap = new QPixmap(pngPlot->toPixmap());
        *pxmap = pxmap->scaled(runningXSize,runningYSize);
        pixVector.push_back(pxmap);
    }

    void Writer::continuousSave() {

        if(saving) {

            // if we have a new screen of data take a snapshot
            if((imageXSize % runningXSize) == 0) {
                takeRunningSnapShot();
            }

            imageXSize++;
        }
    }

    void Writer::finishSaving() {
        // take last snapshot
        takeRunningSnapShot();
        int remainderImageLength = imageXSize % runningXSize;

        // get the max height from the pixmaps
        int maxHieght = 0;
        for (int i = 0; i < pixVector.size(); i++) {
            if(pixVector[i]->height() > maxHieght)
                maxHieght = pixVector[i]->height();
        }

        int pixWidth = pixVector[0]->width();

        // not the elegant way to handle this but it works for now 
        int totalWidth;
        if(remainderImageLength != 0)
            totalWidth = remainderImageLength + (pixWidth * (pixVector.size() - 1));
        else
            totalWidth = pixWidth * pixVector.size();

        QImage *finalImage = new QImage(totalWidth, maxHieght, QImage::Format_RGB32);
        QPainter painter(finalImage);

        int xOffSet = 0;
        for (int i = 0; i < pixVector.size() - 1; i++) {
            painter.drawPixmap(xOffSet, 0, *pixVector[i]);
            xOffSet += pixWidth;
        }

        // add partial of last pixmap
        if(remainderImageLength != 0)
        {
            int startXRemainder = (pixWidth - 1) - remainderImageLength;
            painter.drawPixmap(xOffSet, 0, *pixVector.last(), startXRemainder, 0, remainderImageLength, pixVector.last()->height());
        }

        fixFileName();
        bool success = finalImage->save(fileName, "PNG");
        emit writingDone(success);

        painter.end();
        delete finalImage;
        cleanupPixVector();
    }

    void Writer::cleanupPixVector() {

        for(int i = 0; i < pixVector.size(); i++) {
            delete pixVector[i];
        }

        pixVector.clear();
    }

    void Writer::copyRunningMap() {
        pngColorMap->valueAxis()->setScaleType(runningMap->valueAxis()->scaleType());
        pngColorMap->setInterpolate(runningMap->interpolate());
        pngColorMap->setData(runningMap->data(), true);
        pngColorMap->setGradient(runningMap->gradient());
        pngColorMap->rescaleDataRange(true);
        pngPlot->rescaleAxes();
        pngPlot->replot();
        pngPlot->axisRect()->setAutoMargins(QCP::msNone);
        pngPlot->axisRect()->setMargins(QMargins(0,0,0,0));
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


