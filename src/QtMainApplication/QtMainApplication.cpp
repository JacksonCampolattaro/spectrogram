#include "QtMainApplication.h"

#include <QDebug>

QtMainApplication::QtMainApplication(QWidget *parent) :
        QMainWindow(parent)
{

	// Perhaps this should be statically allocated instead?
	spectrogram = new QtSpectrogram(this);

	setCentralWidget(spectrogram); // IMPORTANT: Do NOT forget this line
	setGeometry(100, 100, 600, 400);
	
	// Partly from media player example code on Qt website
	playButton = new QToolButton(this);
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    // connect(playButton, &QAbstractButton::clicked,
	// 	this, &QtMainApplication::playPressed);
	// Stuff from Therese
	connect(playButton, &QAbstractButton::clicked,
		this, &QtMainApplication::readyPlay);

    stopButton = new QToolButton(this);
    stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    //stopButton->setEnabled(false);

    //connect(stopButton, &QAbstractButton::clicked,
	//	this, &QtMainApplication::stopPressed);
	
	// From Therese
	connect(stopButton, &QAbstractButton::clicked,
		this, &QtMainApplication::readyPause);


	setupSaveButton();

/*
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
*/
	audioSelectBox = new QComboBox(this);
	
	// TODO: Populate the entries with the options from the OS
	//void QComboBox::addItems(const QStringList &texts)
	//QStringList options = new QStringList();
	//audioSelectBox->addItems(QStringList(QString("foo"), QString("bar"), QString("2000"))); // Placeholder
	
	audioSelectBox->addItem("Audio Source 0", QVariant(0));
    audioSelectBox->addItem("Audio Source 1", QVariant(1));
    audioSelectBox->addItem("Audio Source 2", QVariant(2));
    audioSelectBox->setCurrentIndex(0);

	controls = new QToolBar(this);
	//controls->addWidget(playPauseButton);
	controls->addWidget(stopButton);
	controls->addWidget(playButton);
	controls->addWidget(audioSelectBox);
	controls->addWidget(saveButton);
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

/*TODO: (Msg from Therese) I just picked a two-way button stop and start for easy testing.
		Feel free to change it up if you want. 
		https://doc.qt.io/qt-5/qtwidgets-statemachine-twowaybutton-example.html*/
void QtMainApplication::setupSaveButton() {
	/*Picture saving buttons*/
	// TODO: (Msg from Therese) I did a pushbutton because I'm lazy, feel free to make pretty
	saveButton = new QPushButton(this);
	// saveButton = new QToolButton(this);
    // saveButton->setIcon(style()->standardIcon(QStyle::QStyle::SP_DialogSaveButton));

	off = new QState();
    off->assignProperty(saveButton, "text", "Start Saving");
    off->setObjectName("off");

    on = new QState();
    on->assignProperty(saveButton, "text", "Stop Saving");
	on->setObjectName("on");

	off->addTransition(saveButton, &QAbstractButton::clicked, on);
    on->addTransition(saveButton, &QAbstractButton::clicked, off);

	saveMachine.addState(off);
    saveMachine.addState(on);

	saveMachine.setInitialState(off);
	saveMachine.start();

	connect(on, &QState::entered, 
		spectrogram, &QtSpectrogram::startSavePressed);
    connect(on, &QState::exited, 
		spectrogram, &QtSpectrogram::stopSavePressed);
	connect(spectrogram, &QtSpectrogram::pngWritingDone, 
		this, &QtMainApplication::showSaveSuccess);
}
// void QtMainApplication::stopPressed(){
// 	stopButton->setEnabled(false);
// 	playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
// }
/*
void QtMainApplication::playPressed()
{
	switch(playState)
	{
	case stopped:
		//stopButton->setEnabled(true);
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
*/

/*
/// Simple state machine function
void QtMainApplication::playPausePressed()
{
	
	switch (playState) {
    case stopped://QMediaPlayer::StoppedState: // Currently unused
		playPauseButton->setText("Start");

		break;
		
    case paused://QMediaPlayer::PausedState:
		
        playPauseButton->setText("Start");

        break;

    case started://QMediaPlayer::PlayingState:
        playPauseButton->setText("Pause");

        break;
    }
	
}
*/

int QtMainApplication::getAudioSource() const
{
    //return m_rateBox->itemData(m_rateBox->currentIndex()).toDouble();
	return audioSelectBox->itemData(audioSelectBox->currentIndex()).toInt();
}

void QtMainApplication::addAudioSource(int source) // TODO: Finish this
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

void QtMainApplication::updateSources(const DeviceList &deviceList)
{
	this->devices = &deviceList;
	// TODO: Update the list of devices
    emit changeSource(getAudioSource());
}

void QtMainApplication::updateSpectrogram(const Audio::Buffer &buffer) {
	spectrogram->draw(buffer);
}

void QtMainApplication::readyPause() {
	emit pausePressed();
}

void QtMainApplication::readyPlay() {
	// Choose the device indicated by the combobox
	assert(devices);
	const auto &device = (*devices)[getAudioSource()];
	// Start the audio subsystem
	emit playPressed(device, std::chrono::seconds(1), device.sampleRate / 10);
}

// TODO: This can be changed to whatever you want, 
// I just have it printing to console for now for simplicity.
// You could have a pop window appear or a little status message
// show up in the gui or you could get rid of it entirely.
void QtMainApplication::showSaveSuccess(bool success, QString fileName) {
    QString msg;
    if(success) {
        msg = QString("%1 saved to present folder.").arg(fileName);
    }
    else {
        msg = QString("Error: %1 not saved."). arg(fileName);
    }
    
    std::cout << msg.toStdString() << std::endl;
}



