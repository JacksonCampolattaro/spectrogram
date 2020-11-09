#include <QApplication>
#include "GraphGui.h"
#include "QtAudioSystem.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create the GUI
    GraphGui gui;
    gui.show();

    // Create the audio system
    QtAudioSystem audioSystem(std::make_unique<Backend::Soundio>());

    // Link up the signals
    QObject::connect(&audioSystem, &QtAudioSystem::newBufferSignal,
                     &gui, &GraphGui::draw);
    // TODO: There will be other signals to link

    // The GUI doesn't have buttons yet, so we'll have to manually start the backend
    auto device = audioSystem.devices()[2];
    audioSystem.startSlot(device, std::chrono::seconds(2),
                          device.sampleRate / 20);

    // Start the application
    return app.exec();
}
