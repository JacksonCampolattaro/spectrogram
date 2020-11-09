#ifndef PNG_WRITER_H
#define PNG_WRITER_H

#include "qcustomplot.h"
#include <QObject>

namespace Spectrogram::PNG {

    class Writer : public QObject {
    Q_OBJECT

    public:
        explicit Writer(QWidget *parent = 0, QCPColorMap *colorMap = 0, QString nFileName = "snapshot.png");
        void setFileName(QString newFileName);
        QString getFileName();
        void setRunningMap(QCPColorMap *);


    public slots:
        void onWriteSnapShot();

    signals:
        void writingDone(const bool&);


    private:
        void takeSnapShot();
        void fixFileName();
        void copyRunningMap();

        QString fileName;

        QCPColorMap *runningMap;
        QCustomPlot *pngPlot;
        QCPColorMap *pngColorMap;
    };

}

#endif // PNG_WRITER_H