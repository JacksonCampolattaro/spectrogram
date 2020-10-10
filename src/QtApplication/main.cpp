/* main.cpp
 *
 * Course:  ECE 4574
 * Author:  Joshua Lyons
 * Date:    October 10, 2020
 *
 * This is the main entry point of execution for the
 * Sprint 1 Qt GUI of our Spectrogram application.
 *
*/

#include "Qt_Spectrogram.h"

#include <QApplication>
#include <QWidget>

int main(int argc, char **argv) {

    QApplication app(argc, argv);

    QtSpectrogram window;
    window.show();

    return app.exec();
}
