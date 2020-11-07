#ifndef QT_MAIN_APP_H
#define QT_MAIN_APP_H

#include <QMainWindow>
//#include <QMediaPlayer>
#include <QPushButton>
#include <QToolButton>
#include <QComboBox>
#include "SpectrogramGraph.h"

QT_BEGIN_NAMESPACE
//class QComboBox;
enum PlayerState {stopped, started, paused};
QT_END_NAMESPACE

class QtMainApplication : public QMainWindow {
Q_OBJECT

public:
    explicit QtMainApplication(QWidget *parent = 0);
	int getAudioSource() const;

public slots:
	// This slot function can be used publicly to add entries to the list of audio source options
	void setAudioSource(int source);

signals:
	void play();
    void pause();
    void stop();
	
	void changeSource(int source);

	void snapshot(); // TODO: Implement this for the image writer

private slots:
	void playPausePressed();
	void updateSource();

private:
    // Composite GUI objects
	SpectrogramGraph *spectrogram;
	QVBoxLayout *topLevelVLayout;
	QHBoxLayout *buttonLayout;
	
	QPushButton *playPauseButton;
	QDockWidget *wrapPlayPauseButton;

	QComboBox *audioSelectBox;
	QDockWidget *wrapAudioSelectBox;
	
	// State variables
	//QMediaPlayer::State playerState = QMediaPlayer::StoppedState;
	PlayerState playState = stopped;
};

#endif // QT_MAIN_APP_H