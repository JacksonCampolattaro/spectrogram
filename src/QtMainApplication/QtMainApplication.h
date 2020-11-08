#ifndef QT_MAIN_APP_H
#define QT_MAIN_APP_H

#include <QMainWindow>
//#include <QMediaPlayer>
#include <QComboBox>
#include <QPushButton>
#include <QToolButton>
#include <QToolBar>
#include <QGridLayout>
#include "SpectrogramGraph.h"

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
	void setAudioSource(int source); // TODO: Finish this

signals:
	// These are signals for the plot controls, forwarded
	// from their respective button press events
	void play();
    void pause();
    void stop();
	void save();
	void changeSource(int source);

private slots: // TODO: Full implement these
	// These slots are for the UI responses to event
	// signals, after emitting them for other modules
	void playPausePressed();
	void stopPressed();
	void playPressed();
	void saveOutput();
	void updateSource();

private:
    // Composite GUI objects
	SpectrogramGraph *spectrogram;
	//QGridLayout *appLayout;	
	//QVBoxLayout *topLevelVLayout;
	//QHBoxLayout *buttonLayout;
	QToolBar *controls;
	
	QToolButton *stopButton;
	QToolButton *playButton;
	QToolButton *saveButton;

	QPushButton *playPauseButton;
	QComboBox *audioSelectBox;
	
	// State variable(s)
	PlayerState playState = stopped;
};

#endif // QT_MAIN_APP_H