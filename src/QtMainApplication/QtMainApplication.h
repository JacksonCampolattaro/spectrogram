#ifndef QT_MAIN_APP_H
#define QT_MAIN_APP_H

#include <QMainWindow>
//#include <QMediaPlayer>
#include <QComboBox>
#include <QPushButton>
#include <QToolButton>
#include <QToolBar>
#include <QGridLayout>
#include "Spectrogram/Visualizer/QtSpectrogram.h"
#include "Spectrogram/Visualizer/QtAudioSystem.h"

#include <Spectrogram/Audio/DeviceList.h>

//QT_MAIN_APP_BEGIN_NAMESPACE
enum PlayerState {stopped, started, paused};
//QT_MAIN_APP_END_NAMESPACE

class QtMainApplication : public QMainWindow {
Q_OBJECT

public:
    explicit QtMainApplication(QWidget *parent = 0);
	int getAudioSource() const; // TODO: Finish this

public slots:
	// This slot function can be used publicly to add entries to the list of audio source options
	void updateSpectrogram(const Audio::Buffer &buffer);

	void updateSources(const DeviceList &deviceList);

	void startButtonClicked();

	void showSaveSuccess(bool success, QString fileName);

signals:
	// These are signals for the plot controls, forwarded
	// from their respective button press events
	void startSignal(const Device &device, std::chrono::milliseconds maxLatency, size_t bufferLength);
    void stopSignal();

	void changeSource(int source);

private slots: // TODO: Full implement these
	// These slots are for the UI responses to event
	// signals, after emitting them for other modules
	//void playPausePressed();
	// void readyPause();
	// void readyPlay();
	//void saveOutput();

private:
	void setupSaveButton();

    // Composite GUI objects
	QtSpectrogram *spectrogram;
	//QGridLayout *appLayout;	
	//QVBoxLayout *topLevelVLayout;
	//QHBoxLayout *buttonLayout;
	QToolBar *controls;
	
	QToolButton *stopButton; //OPTIONAL, YES CHOSEN
	QToolButton *startButton; //OPTIONAL, YES CHOSEN

	QPushButton *saveButton; 
	QStateMachine saveMachine;
	QState *off;
	QState *on;
	//QToolButton *saveButton;

	//QPushButton *playPauseButton;  //OPTIONAL, NOT CHOSEN
	QComboBox *audioSelectBox;
	
	// State variable(s)
	PlayerState playState = paused;

	const DeviceList *devices = nullptr;

};

#endif // QT_MAIN_APP_Ha