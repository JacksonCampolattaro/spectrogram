#include "QtApplication.h"

#include <QDebug>
#include <QSlider>
#include <QScreen>
#include <QStyleHints>
//qDebug() << "insert message";
/***
 * Links to reference pages I used, might help with debugging
 ***
 MOST IMPORTANT
	https://doc.qt.io/qt-5/qmainwindow.html#createPopupMenu
	https://doc.qt.io/qt-5/qtwidgets-widgets-windowflags-example.html
	
	https://doc.qt.io/archives/qt-5.6/qtmultimedia-multimediawidgets-player-player-cpp.html
	
	https://doc.qt.io/qt-5/qdialog.html

Full App Examples
	https://doc.qt.io/qt-5/qtexamplesandtutorials.html
	https://doc.qt.io/archives/qt-5.6/qtmultimedia-multimediawidgets-player-example.html
	https://doc.qt.io/qt-5/qtwidgets-mainwindows-application-example.html
	
Pop-out Window
	https://doc.qt.io/qt-5/qmainwindow.html#createPopupMenu
	https://doc.qt.io/qt-5/qdialog.html
		https://doc.qt.io/qt-5/qtwidgets-dialogs-standarddialogs-example.html
	https://doc.qt.io/qt-5/qmessagebox.html
	https://doc.qt.io/qt-5/qdockwidget.html

Layout
	https://doc.qt.io/qt-5/examples-layouts.html
	https://doc.qt.io/qt-5/qtwidgets-widgets-groupbox-example.html
	https://doc.qt.io/qt-5/qtwidgets-layouts-basiclayouts-example.html
	https://doc.qt.io/qt-5/qformlayout.html

Individual UI Elements
	https://doc.qt.io/qt-5/qspinbox.html
	https://doc.qt.io/qt-5/qcheckbox.html
	https://doc.qt.io/qt-5/qcombobox.html
	https://doc.qt.io/qt-5/qstyle.html#StandardPixmap-enum
 *
 ***/

QtApplication::QtApplication(QWidget *parent) :
        QMainWindow(parent) {

    // Set the size of the window, and it's initial location on the user's screen
    winBounds = new QRect(
				100, 100, 600, 400);
	setGeometry(100, 100, 600, 400);
	//resize(500, 300);

    // Create a new spectrogram widget, giving qt ownership
    spectrogram = new QtSpectrogram(this);
	//connect(this, SIGNAL(settingsChanged(const Settings::Profile &settings)),
	connect(this, &QtApplication::settingsChanged,
            this, &QtApplication::applySettingsProfile);
//			spectrogram, &QtSpectrogram::changeSettings);
			//spectrogram, SLOT(changeSettings(const Settings::Profile &settings)));

    // The spectrogram is the only central widget, with everything else in a toolbar
    // TODO: If we want to change that, we can simply make the central widget a VBox!
    setCentralWidget(spectrogram);

    // A button to start the spectrogram, with a play icon
    startButton = new QToolButton(this);
    startButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    // When this button is clicked, we should signal the backend
    connect(startButton, &QAbstractButton::clicked,
            this, &QtApplication::startButtonClicked);

    // A button to stop the spectrogram, with a stop icon
    stopButton = new QToolButton(this);
    stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));

    // We can chain signals so that the stop button directly triggers the stop signal
    connect(stopButton, &QAbstractButton::clicked,
            this, &QtApplication::stopSignal);

    // This creates the UI element that toggles saving data
    setupSaveButton();

    // The combobox will be empty by default, at least until we're told what devices are available
    audioSelectBox = new QComboBox(this);
    audioSelectBox->setDisabled(true);

    // This creates the UI element to change settings
	settingsButton = new QPushButton("Settings", this);
	connect(settingsButton, &QAbstractButton::clicked,
            this, &QtApplication::showSettings);
			//this, SLOT(showSettings()));
			//setEnabled(available);
	
	// Create a toolbar, and add all our buttons to it
    controls = new QToolBar(this);
    controls->addWidget(stopButton);
    controls->addWidget(startButton);
    controls->addWidget(audioSelectBox);
    controls->addWidget(saveButton);
	controls->addWidget(settingsButton);

    // We'll put the toolbar at the top of the screen
    addToolBar(Qt::TopToolBarArea, controls);

	settingsWindow = 0;
	setupSettingsWindow();

	qDebug() << "*end of initialization reached*";
}

/*https://doc.qt.io/qt-5/qtwidgets-statemachine-twowaybutton-example.html*/
void QtApplication::setupSaveButton() {
    /*Picture saving buttons*/
    // TODO: Feel free to change the look of the buttton
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
            this, &QtApplication::showSaveSuccess);
}

// Similar to a custom implementation of
// 		[virtual]QMenu *QMainWindow::createPopupMenu()
void QtApplication::setupSettingsWindow() {
		
	qDebug() << "*open settings window command issued*";
	
	//settingsWindow = new QDialog();
	//settingsWindow->setParent(nullptr); // Need to manually change the parent?
	//settingsWindow->setModal(true);	// Prevent user from interacting with main window until finished with popout	
	
	//plotSettings->colorScheme = "";

	if (!settingsWindow) {

		//QFormLayout *settingsWindowLayout;
		//QComboBox *colorSchemeSelectBox; // 0 by default
		colorSchemeSelectBox = new QComboBox();
		colorSchemeSelectBox->setDisabled(false);
		
		colorSchemeSelectBox->addItem("grayscale");
		colorSchemeSelectBox->addItem("hot");
		colorSchemeSelectBox->addItem("cold");
		colorSchemeSelectBox->addItem("night");
		colorSchemeSelectBox->addItem("candy");
		colorSchemeSelectBox->addItem("geography");
		colorSchemeSelectBox->addItem("ion");
		colorSchemeSelectBox->addItem("thermal");
		colorSchemeSelectBox->addItem("polar");
		colorSchemeSelectBox->addItem("spectrum");
		colorSchemeSelectBox->addItem("jet");
		colorSchemeSelectBox->addItem("hues");
		
		colorSchemeSelectBox->setCurrentIndex(0); // Grayscale by default

		//QSpinBox *frameRateBox;	// 20 by default
		frameRateBox = new QSpinBox();
		frameRateBox->setRange(5, 60);
		frameRateBox->setValue(20);
		frameRateBox->setSingleStep(5);

		//QCheckBox *isLogBox;	// True by default
		isLogBox = new QCheckBox();
		isLogBox->setCheckable(true);
		isLogBox->setChecked(true);
		

        QFormLayout *formLayout = new QFormLayout;
        //formLayout->addRow(tr("Brightness"), brightnessSlider);
        //formLayout->addRow(tr("Contrast"), contrastSlider);
        //formLayout->addRow(tr("Hue"), hueSlider);
        //formLayout->addRow(tr("Saturation"), saturationSlider);
		formLayout->addRow(tr("Color Scheme:"), colorSchemeSelectBox);
		formLayout->addRow(tr("Frame Rate:"), frameRateBox);
		formLayout->addRow(tr("Log Scale:"), isLogBox);


		discardSettingsButton = new QPushButton("Cancel");
		//connect(discardSettingsButton, &QPushButton::clicked,
		//        settingsWindow, &QDialog::close);
		//connect(discardSettingsButton, SIGNAL(clicked()), settingsWindow, SLOT(close()));
		//connect(discardSettingsButton, &QPushButton::clicked,
		//        this, settingsWindow->close());
		//connect(discardSettingsButton, &QPushButton::clicked,
		//        settingsWindow, SLOT(&QDialog::reject)());

		saveSettingsButton = new QPushButton("Save");
		saveSettingsButton->setDefault(true);
		connect(saveSettingsButton, &QAbstractButton::clicked,
				this, &QtApplication::saveSettingsClicked);
		//		this, &QtApplication::settingsChanged);
				//settingsChanged(const Settings::Profile &settings);

		//QPushButton *button = new QPushButton("Close");
        //layout->addRow(button);

		//QVBoxLayout *vboxWindowLayout = new QVBoxLayout;
		settingsWindowLayout = new QVBoxLayout;
		settingsWindowLayout->addLayout(formLayout);

		QHBoxLayout *hboxLayout = new QHBoxLayout;
		hboxLayout->addWidget(saveSettingsButton);
		hboxLayout->addWidget(discardSettingsButton);
		settingsWindowLayout->addLayout(hboxLayout);

        settingsWindow = new QDialog(this);
        settingsWindow->setWindowTitle("Plot Settings");
        settingsWindow->setModal(true);
		settingsWindow->setLayout(settingsWindowLayout);

		/*
		if (!QGuiApplication::styleHints()->showIsFullScreen() && !QGuiApplication::styleHints()->showIsMaximized()) {
		    
			const QRect availableGeometry = *(this->winBounds);

		    settingsWindow->resize(availableGeometry.width() / 3, availableGeometry.height() * 2 / 3);
		    settingsWindow->move((availableGeometry.width() - settingsWindow->width()) / 2,
		                		(availableGeometry.height() - settingsWindow->height()) / 2);
		}
		*/

        //connect(button, SIGNAL(clicked()), settingsWindow, SLOT(close()));
    }
    
	//settingsWindow->show();
	//settingsWindow->popup();
	//settingsWindow->exec();
}

void QtApplication::showSettings(){
	
	if(!settingsWindow){
		qDebug() << "*Error: invalid open settings window command issued*";
		return;
	}
	
	//emit stopSignal();
	//if(saveMachine.on){
	//	startButtonClicked();
	//}

	qDebug() << "*open settings window command issued*";
	//settingsWindow->exec();
	
	// Refresh the stored state of each UI element
	colorSchemeSelectBox->setCurrentIndex(plotSettings.colorScheme);
	frameRateBox->setValue(plotSettings.framesPerSecond);
	isLogBox->setChecked(plotSettings.logscale);

	/*** Important-ish Note:
	 * There was conflicting info on whther to use show() or
	 * exec() for dialog windows like this, so might try both
	 * ***/
	settingsWindow->show();
	//settingsWindow->popup();
	//settingsWindow->exec();
}

void QtApplication::saveSettingsClicked(){
	
	//Settings::Profile &settings;
	plotSettings.colorScheme = colorSchemeSelectBox->currentIndex(); // 0 by default
	plotSettings.framesPerSecond = frameRateBox->value();	// 20 by default
	plotSettings.logscale = isLogBox->isChecked();	// True by default

	emit settingsChanged(plotSettings);

	/***Re-draw canvas here??***/
	settingsWindow->close();
	
	//startButtonClicked();
}

void QtApplication::updateSources(const DeviceList &deviceList) {

    // Update the stored device list
    this->devices = &deviceList;

    // Clear the combobox
    audioSelectBox->clear();

    // Add options to the combobox
    for (auto &device : deviceList) {
        audioSelectBox->addItem(QString::fromStdString(device.name), QVariant(device.id));
    }

    // Enable device selection
    audioSelectBox->setEnabled(true);
}

void QtApplication::updateSpectrogram(const Audio::Buffer &buffer) {
    spectrogram->draw(buffer);
}

void QtApplication::startButtonClicked() {

    // The device list _must_ be set before starting
    assert(devices);

    // Choose the device indicated by the combobox
    const auto &device = (*devices)[audioSelectBox->currentData().toInt()];

    // Start the audio subsystem
    emit startSignal(device, std::chrono::seconds(2), device.sampleRate / (framesPerSecond / 2.0));
}

// TODO: This can be changed to whatever you want, 
// I just have it printing to console for now for simplicity.
// You could have a pop window appear or a little status message
// show up in the gui or you could get rid of it entirely.
void QtApplication::showSaveSuccess(bool success, QString fileName) {
    QString msg;
    if (success) {
        msg = QString("%1 saved to present folder.").arg(fileName);
    } else {
        msg = QString("Error: %1 not saved.").arg(fileName);
    }

    std::cout << msg.toStdString() << std::endl;
}

void QtApplication::applySettingsProfile(const Settings::Profile &settings) {

    // Might as well stop the program, when settings are changed!
    emit stopSignal();

    // The next run will be started with a higher framerate
    framesPerSecond = settings.framesPerSecond;

	// Initialize frontend settings state
	plotSettings.colorScheme = settings.colorScheme;
	plotSettings.framesPerSecond = settings.framesPerSecond;
	plotSettings.logscale = settings.logscale;

	// Set the spectrogram formatting
	spectrogram->changeSettings(settings);
	//emit settingsChanged(settings);
}

