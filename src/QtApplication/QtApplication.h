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

#include "Spectrogram/Settings/Profile.h"
#include "QtAudioSystem.h"

class QtApplication : public QMainWindow {
Q_OBJECT

public:
    explicit QtApplication(QWidget *parent = nullptr);

public slots:

    // Connected in main.cpp to slot:
	// &audioSystem, &QtAudioSystem::newBufferSignal
	void updateSpectrogram(const Audio::Buffer &buffer);

    // This slot is manually called in main.cpp during setup to
	// "tell the gui what devices are available"
	void updateSources(const DeviceList &deviceList);

	// This slot is manually called in main.cpp to initialize
	// the plot with profile settings stored in spectrogram.rc
	void changeSpectrogramSettings(const Settings::Profile &settings);

	// Triggers the popup settings window
	void showSettings();
    
	void startButtonClicked();

    void showSaveSuccess(bool success, QString fileName);


signals:

    // These are signals for the plot controls, forwarded
    // from their respective button press events
    
	// Connected in main.cpp, to slot:
	// &audioSystem, &QtAudioSystem::stopSlot
	void startSignal(const Device &device, std::chrono::milliseconds maxLatency, size_t bufferLength);

    // Connected in main.cpp, to slot:
	// &audioSystem, &QtAudioSystem::startSlot
	void stopSignal();

	// Connected in QtApplication.cpp, to slot: 
	// &spectrogram, &QtSpectrogram::changeSettings
	void settingsChanged(const Settings::Profile &settings);


private slots:
	
	// An intermediary function to collect the states of
	// each UI element into a Settings object, then send it
	// to the backend via signal
	void saveSettingsClicked();

private:

    void setupSaveButton();
	void setupSettingsWindow();

    QtSpectrogram *spectrogram;

    QRect *winBounds;
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
	Settings::Profile plotSettings;
	QDialog *settingsWindow;

	//QFormLayout *settingsWindowLayout;
	QVBoxLayout *settingsWindowLayout;
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