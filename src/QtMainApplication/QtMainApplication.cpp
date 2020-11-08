#include "QtMainApplication.h"

#include <QDebug>

QtMainApplication::QtMainApplication(QWidget *parent) :
        QMainWindow(parent)
{
    // Perhaps this should be statically allocated instead?
	spectrogram = new SpectrogramGraph(this);
	
	setCentralWidget(spectrogram); // IMPORTANT: Do NOT forget this line
	setGeometry(100, 100, 500, 400);
	
	// Partly from media player example code on Qt website
	playButton = new QToolButton(this);
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    connect(playButton, &QAbstractButton::clicked, this, &QtMainApplication::play);

    stopButton = new QToolButton(this);
    stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    stopButton->setEnabled(false);

    connect(stopButton, &QAbstractButton::clicked, this, &QtMainApplication::stop);

	saveButton = new QToolButton(this);
    saveButton->setIcon(style()->standardIcon(QStyle::QStyle::SP_DialogSaveButton));

    connect(saveButton, &QAbstractButton::clicked, this, &QtMainApplication::saveOutput);
	
	
	// Standard PushButton approach (for comparison)
	playPauseButton = new QPushButton(this);
	playPauseButton->setObjectName(QStringLiteral("playPauseButton"));
	playPauseButton->setCheckable(true);
	playPauseButton->setChecked(false);
	QFont font;
	font.setPointSize(10);
	playPauseButton->setFont(font);
	playPauseButton->setText("Start");
	
	connect(playPauseButton, &QAbstractButton::clicked,
		this, &QtMainApplication::playPausePressed);

	audioSelectBox = new QComboBox(this);
	
	// TODO: Populate the entries with the options from the OS
	//void QComboBox::addItems(const QStringList &texts)
	//QStringList options = new QStringList();
	//audioSelectBox->addItems(QStringList(QString("foo"), QString("bar"), QString("2000"))); // Placeholder
	
	audioSelectBox->addItem("Audio Source 0", QVariant(0));
    audioSelectBox->addItem("Audio Source 1", QVariant(1));
    audioSelectBox->addItem("Audio Source 2", QVariant(2));
    audioSelectBox->setCurrentIndex(0);

	QObject::connect(audioSelectBox, QOverload<int>::of(&QComboBox::activated),
		this, &QtMainApplication::updateSource);

	controls = new QToolBar(this);
	controls->addWidget(playPauseButton);
	controls->addWidget(saveButton);
	controls->addWidget(stopButton);
	controls->addWidget(playButton);
	controls->addWidget(audioSelectBox);
	addToolBar(Qt::TopToolBarArea, controls);
/*
	/// Alternate approach if the class is extending plain old QWidget ///
	appLayout = new QGridLayout(this);
	appLayout->addWidget(saveButton,		0, 0, 1, 1);
	appLayout->addWidget(playPauseButton,	0, 1, 2, 1);
	appLayout->addWidget(stopButton,		0, 2, 1, 1);
	appLayout->addWidget(playButton,		0, 3, 1, 1);
	appLayout->addWidget(audioSelectBox,	0, 4, 1, 1);
	appLayout->addWidget(spectrogram,		1, 0, -1, -1);
*/
}

void QtMainApplication::stopPressed(){
	stopButton->setEnabled(false);
	playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
}

void QtMainApplication::playPressed()
{
	switch(playState)
	{
	case stopped:
		stopButton->setEnabled(true);
		playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
		break;
	case started:
		stopButton->setEnabled(false);
		playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
		break;
	case paused:
		stopButton->setEnabled(false);
		playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
		break;
	}
}

void QtMainApplication::saveOutput(){
	// Stub
}

/// Simple state machine function
void QtMainApplication::playPausePressed()
{
	switch (playState) {
    case stopped://QMediaPlayer::StoppedState: // Currently unused
		playPauseButton->setText("Start");
		emit play();
		break;
    case paused://QMediaPlayer::PausedState:
        playPauseButton->setText("Resume");
		emit play();
        break;
    case started://QMediaPlayer::PlayingState:
        playPauseButton->setText("Stop");
		emit pause();
        break;
    }
}

int QtMainApplication::getAudioSource() const
{
    //return m_rateBox->itemData(m_rateBox->currentIndex()).toDouble();
	return audioSelectBox->itemData(audioSelectBox->currentIndex()).toInt();
}

void QtMainApplication::setAudioSource(int source)
{
    for (int i = 0; i < audioSelectBox->count(); ++i) {
        //if (qFuzzyCompare(source, float(audioSelectBox->itemData(i).toDouble()))) {
		if (source == audioSelectBox->itemData(i).toInt()) {
            audioSelectBox->setCurrentIndex(i);
            return;
        }
    }

    audioSelectBox->addItem(QString("%1x").arg(source), QVariant(source));
    audioSelectBox->setCurrentIndex(audioSelectBox->count() - 1);
}

void QtMainApplication::updateSource()
{
    emit changeSource(getAudioSource());
}