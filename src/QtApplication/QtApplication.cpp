#include "QtApplication.h"

#include <QDebug>

QtApplication::QtApplication(QWidget *parent) :
        QMainWindow(parent) {

    // Set the size of the window, and it's initial location on the user's screen
    setGeometry(100, 100, 600, 400);

    // Create a new spectrogram widget, giving qt ownership
    spectrogram = new QtSpectrogram(this);

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

    // Create a toolbar, and add all our buttons to it
    controls = new QToolBar(this);
    controls->addWidget(stopButton);
    controls->addWidget(startButton);
    controls->addWidget(audioSelectBox);
    controls->addWidget(saveButton);

    // We'll put the toolbar at the top of the screen
    addToolBar(Qt::TopToolBarArea, controls);

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
    emit startSignal(device, std::chrono::seconds(2), device.sampleRate / 10);
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

void QtApplication::changeSpectrogramSettings(const Settings::Profile &settings) {
    spectrogram->changeSettings(settings);
}

