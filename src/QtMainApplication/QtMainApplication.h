#ifndef QT_MAIN_APP_H
#define QT_MAIN_APP_H

#include <QMainWindow>
//#include <QMediaPlayer>
#include <QComboBox>
#include <QPushButton>
#include <QToolButton>
#include <QToolBar>
#include <QGridLayout>
#include <QThread>
#include "Spectrogram/Visualizer/QtSpectrogram.h"
#include "Spectrogram/Visualizer/QtAudioSystem.h"

#include <Spectrogram/Audio/DeviceList.h>
#include <Spectrogram/PNG/Writer.h>

//QT_MAIN_APP_BEGIN_NAMESPACE
enum PlayerState {stopped, started, paused};
//QT_MAIN_APP_END_NAMESPACE

class QtMainApplication : public QMainWindow {
Q_OBJECT

public:
    explicit QtMainApplication(QWidget *parent = 0);
	~QtMainApplication();
	int getAudioSource() const; // TODO: Finish this

public slots:
	// This slot function can be used publicly to add entries to the list of audio source options
	void addAudioSource(int source); // TODO: Finish this
	void updateSpectrogram(const Audio::Buffer &buffer);
	void updateSources(const DeviceList &deviceList);
	void readyPause();
	void readyPlay();
	void showSaveSuccess(bool success);

signals:
	// These are signals for the plot controls, forwarded
	// from their respective button press events
	void playPressed(const Device &device, std::chrono::milliseconds maxLatency, size_t bufferLength);
    void pausePressed();
    //void stopPressed();
	void savePressed();
	
	void changeSource(int source);

private slots: // TODO: Full implement these
	// These slots are for the UI responses to event
	// signals, after emitting them for other modules
	//void playPausePressed();
	// void readyPause();
	// void readyPlay();
	void saveOutput();

private:
	void setupPngWriter();
    // Composite GUI objects
	QtSpectrogram *spectrogram;
	//QGridLayout *appLayout;	
	//QVBoxLayout *topLevelVLayout;
	//QHBoxLayout *buttonLayout;
	QToolBar *controls;
	
	QToolButton *stopButton; //OPTIONAL, YES CHOSEN
	QToolButton *playButton; //OPTIONAL, YES CHOSEN
	QToolButton *saveButton;

	//QPushButton *playPauseButton;  //OPTIONAL, NOT CHOSEN
	QComboBox *audioSelectBox;
	
	// State variable(s)
	PlayerState playState = paused;

	const DeviceList *devices = nullptr;

	QThread writerThread;
	Spectrogram::PNG::Writer *pngWriter;
};

#endif // QT_MAIN_APP_Ha