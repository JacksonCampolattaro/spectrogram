#include "QtMainApplication.h"



QtMainApplication::QtMainApplication(QWidget *parent) :
        QMainWindow(parent)
{
    spectrogram = new SpectrogramGraph(this);

    setCentralWidget(spectrogram);
    setGeometry(100, 100, 500, 400);
}


