#ifndef PNG_WRITER_H
#define PNG_WRITER_H

#include "qcustomplot.h"
#include <QObject>

namespace Spectrogram::PNG {

    class Writer : public QObject {
    Q_OBJECT

    public:
        explicit Writer(QWidget *parent = 0, QCPColorMap *colorMap = 0, QString nFileName = "snapshot.png");
        ~Writer();
        void setFileName(QString newFileName);
        QString getFileName();
        void setRunningMap(QCPColorMap *);


    public slots:
        void continuousSave();
        void onStartSaving();
        void onStopSaving();

    signals:
        void writingDone(bool);


    private:
        void takeRunningSnapShot();
        void fixFileName();
        void copyRunningMap();
        void finishSaving();
        void cleanupPixVector();

        QString fileName;

        QCPColorMap *runningMap;
        QCustomPlot *pngPlot;
        QCPColorMap *pngColorMap;

        QVector<QPixmap*> pixVector;
        bool saving;
        int imageXSize;
        int runningXSize;
        int runningYSize;
    };

}

#endif // PNG_WRITER_H