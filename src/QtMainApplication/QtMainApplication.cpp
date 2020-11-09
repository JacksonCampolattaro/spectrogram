#include "QtMainApplication.h"

#include <QDebug>

QtMainApplication::QtMainApplication(QWidget *parent) :
        QMainWindow(parent)
{

	// Perhaps this should be statically allocated instead?
	spectrogram = new QtSpectrogram(this);

	setCentralWidget(spectrogram); // IMPORTANT: Do NOT forget this line
	setGeometry(100, 100, 500, 400);
	
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

	saveButton = new QToolButton(this);
    saveButton->setIcon(style()->standardIcon(QStyle::QStyle::SP_DialogSaveButton));


	connect(saveButton, &QAbstractButton::clicked,
		this, &QtMainApplication::saveOutput);
	

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
	controls->addWidget(saveButton);
	controls->addWidget(stopButton);
	controls->addWidget(playButton);
	controls->addWidget(audioSelectBox);
	addToolBar(Qt::TopToolBarArea, controls);

	setupPngWriter();
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
QtMainApplication::~QtMainApplication() {
    writerThread.quit();
    writerThread.wait();
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

void QtMainApplication::saveOutput() {
	emit savePressed();
}

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

		// FIXME: Which case is relevant here?

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
	const auto &device = (*devices)[1]; // For now, just choose the first device
	// Start the audio subsystem
	emit playPressed(device, std::chrono::seconds(2), device.sampleRate / 10);
}

// Needs to be in it's own thread so that when it's updated to save 
// continuously it wont interfere with gui when it does computationally 
// expensive picture appending.
void QtMainApplication::setupPngWriter()
{
    pngWriter = new Spectrogram::PNG::Writer();
    pngWriter->setFileName("snapshot.png");
	// pngWriter will never modify the spectrogram's colorMap, 
	// it just needs it to copy its data periodically
	pngWriter->setRunningMap(spectrogram->getColorMapPtr());
    pngWriter->moveToThread(&writerThread);

    connect(&writerThread, &QThread::finished, pngWriter, &QObject::deleteLater);
    connect(this, &QtMainApplication::savePressed, pngWriter, &Spectrogram::PNG::Writer::onWriteSnapShot);
    connect(pngWriter, &Spectrogram::PNG::Writer::writingDone, this, &QtMainApplication::showSaveSuccess);
    writerThread.start();
}

// TODO: This can be changed to whatever you want, 
// I just have it printing to console for now for simplicity.
// You could have a pop window appear or a little status message
// show up in the gui or you could get rid of it entirely.
void QtMainApplication::showSaveSuccess(bool success) {
    QString msg;
    QString fileName = pngWriter->getFileName();
    if(success) {
        msg = QString("%1 saved to present folder.").arg(fileName);
    }
    else {
        msg = QString("Error: %1 not saved."). arg(fileName);
    }
    
    std::cout << msg.toStdString() << std::endl;
}



