#include <QApplication>
#include <QMainWindow>
#include "Spectrogram/Visualizer/QtSpectrogram.h"
#include "Spectrogram/Visualizer/QtAudioSystem.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create the GUI
    QMainWindow gui;
    QtSpectrogram spectrogram(&gui);
    gui.setGeometry(100, 100, 1500, 700);
    gui.setCentralWidget(&spectrogram);
    gui.show();

    // Create the audio system
    QtAudioSystem audioSystem(std::make_unique<Backend::Soundio>());

    // Link up the signals
    QObject::connect(&audioSystem, &QtAudioSystem::newBufferSignal,
                     &spectrogram, &QtSpectrogram::draw);
    // TODO: There will be other signals to link

    // The GUI doesn't have buttons yet, so we'll have to manually start the backend
    auto device = audioSystem.devices()[1];
    audioSystem.startSlot(device, std::chrono::seconds(2),
                          device.sampleRate / 60);

    // Start the application
    return app.exec();
}
