#ifndef QT_MAIN_APP_H
#define QT_MAIN_APP_H

#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QToolButton>
#include <QToolBar>
#include <QGridLayout>

#include <Spectrogram/Visualizer/QtSpectrogram.h>
#include <Spectrogram/Audio/DeviceList.h>

#include "QtAudioSystem.h"

class QtApplication : public QMainWindow {
Q_OBJECT

public:
    explicit QtApplication(QWidget *parent = nullptr);

public slots:

    void updateSpectrogram(const Audio::Buffer &buffer);

    void updateSources(const DeviceList &deviceList);

    void startButtonClicked();

    void showSaveSuccess(bool success, QString fileName);

    void changeSpectrogramSettings(const Settings::Profile &settings);

signals:

    // These are signals for the plot controls, forwarded
    // from their respective button press events
    void startSignal(const Device &device, std::chrono::milliseconds maxLatency, size_t bufferLength);

    void stopSignal();

private:
    void setupSaveButton();

    QtSpectrogram *spectrogram;

    QToolBar *controls;

    QToolButton *stopButton;
    QToolButton *startButton;

    QComboBox *audioSelectBox;

    QPushButton *saveButton;
    QStateMachine saveMachine;
    QState *off;
    QState *on;

    const DeviceList *devices = nullptr;

    size_t framesPerSecond = 10;

};

#endif // QT_MAIN_APP_Ha