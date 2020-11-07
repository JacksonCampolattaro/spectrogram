#include "QtMainApplication.h"

//#include <QMediaPlayer>

QtMainApplication::QtMainApplication(QWidget *parent) :
        QMainWindow(parent)
{
    // Perhaps this should be statically allocated instead?
	spectrogram = new SpectrogramGraph(this);

    setCentralWidget(spectrogram);
    setGeometry(100, 100, 500, 400);
/*
	topLevelVLayout = new QVBoxLayout(this);
	topLevelVLayout->addWidget(spectrogram);

	buttonLayout = new QHBoxLayout(this);
	buttonLayout->setContentsMargins(0, 0, 0, 0);
*/
	// From media player example code on Qt website, not quite ready to implement it this way yet
/*
	m_playButton = new QToolButton(this);
    m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    connect(m_playButton, &QAbstractButton::clicked, this, &PlayerControls::playClicked);

    m_stopButton = new QToolButton(this);
    m_stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    m_stopButton->setEnabled(false);

    connect(m_stopButton, &QAbstractButton::clicked, this, &PlayerControls::stop);
*/

	playPauseButton = new QPushButton(this);
	playPauseButton->setObjectName(QStringLiteral("playPauseButton"));
	playPauseButton->setCheckable(true);
	playPauseButton->setChecked(false);
		QFont font;
        font.setPointSize(10);
        playPauseButton->setFont(font);
		playPauseButton->setText("Play");
	//playPauseButton->setM
	connect(playPauseButton, &QAbstractButton::clicked,
		this, &QtMainApplication::playPausePressed);
/*
	buttonLayout->addWidget(playPauseButton);

	audioSelectBox = new QComboBox();
	
	buttonLayout->addWidget(audioSelectBox);

	topLevelVLayout->addWidget((QWidget*)buttonLayout);
	//topLevelVLayout->addLayout(buttonLayout);
	//this->setLayout(topLevelVLayout);
*/
	//auto wrapPlayPauseButton = new QDockWidget();
	
	wrapPlayPauseButton = new QDockWidget(this);
	wrapPlayPauseButton->setWidget(playPauseButton);
	this->addDockWidget(Qt::TopDockWidgetArea, wrapPlayPauseButton);
	
	audioSelectBox = new QComboBox(this);
	//audioSelectBox->setPlaceholderText("Select an Audio Source...");
	audioSelectBox->setCurrentText("Select an Audio Source...");
	
	// TODO: Populate the entries with the options from the OS
	//void QComboBox::addItems(const QStringList &texts)
	//QStringList options = new QStringList();
	//audioSelectBox->addItems(QStringList(QString("foo"), QString("bar"), QString("2000"))); // Placeholder
	wrapAudioSelectBox = new QDockWidget(this);
	wrapAudioSelectBox->setWidget(audioSelectBox);
	this->addDockWidget(Qt::TopDockWidgetArea, wrapPlayPauseButton);

	connect(audioSelectBox, QOverload<int>::of(&QComboBox::activated),
		this, &QtMainApplication::updateSource);
}

/// Simple state machine function
void QtMainApplication::playPausePressed()
{
    switch (playState) {
    case stopped://QMediaPlayer::StoppedState: // Currently unused
    case paused://QMediaPlayer::PausedState:
        emit play();
        break;
    case started://QMediaPlayer::PlayingState:
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