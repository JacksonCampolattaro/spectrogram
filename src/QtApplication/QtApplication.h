#ifndef QT_MAIN_APP_H
#define QT_MAIN_APP_H

#include <QMainWindow>
#include <QDialog>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QPushButton>
#include <QToolButton>
#include <QToolBar>
#include <QGridLayout>
#include <QFormLayout>

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

	void showSettings();

signals:

    // These are signals for the plot controls, forwarded
    // from their respective button press events
    void startSignal(const Device &device, std::chrono::milliseconds maxLatency, size_t bufferLength);

    void stopSignal();

	void settingsChanged(const Settings::Profile &settings);

private:
    void setupSaveButton();
	void setupSettingsWindow();

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

	QPushButton *settingsButton;

	// TODO: Pull this out into its own class that extends QDialog
	Settings::Profile *plotSettings;
	QDialog *settingsWindow;

	QFormLayout *settingsWindowLayout;
	QComboBox *colorSchemeSelectBox; // 0 by default
	QSpinBox *frameRateBox;	// 20 by default
	QCheckBox *isLogBox;	// True by default
	
	QPushButton *saveSettingsButton;
	QPushButton *discardSettingsButton;

	// These are encapsulated in the Settings object
	size_t framesPerSecond = 10;
	//bool logscale = true;
	//int colorScheme = 0;

};

#endif // QT_MAIN_APP_Ha