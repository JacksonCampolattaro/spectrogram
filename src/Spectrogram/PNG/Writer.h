#ifndef PNG_WRITER_H
#define PNG_WRITER_H

#include "qcustomplot.h"
#include <QObject>

namespace Spectrogram::PNG {

    class Writer : public QObject {
    Q_OBJECT

    public:
        explicit Writer(QWidget *parent = 0, QString nFileName = "snapshot.png");
        void setFileName(QString newFileName);
        QString getFileName();

    public slots:
        void onWritePng(QCPColorMapData*);
        void onGradiantChanged(const QCPColorGradient &);

    signals:
        void writingDone(const bool&);


    private:
        void takeSnapShot(QCPColorMapData *);
        void fixFileName(const int &);

        QString fileName;

        QCustomPlot *pngPlot;
        QCPColorMap *pngColorMap;
    };

}

#endif // PNG_WRITER_H