#ifndef QT_MAIN_APP_H
#define QT_MAIN_APP_H

#include <QMainWindow>
#include "SpectrogramGraph.h"

class QtMainApplication : public QMainWindow {
Q_OBJECT

public:
    explicit QtMainApplication(QWidget *parent = 0);

public slots:


private:
    SpectrogramGraph *spectrogram;

};

#endif // QT_MAIN_APP_H