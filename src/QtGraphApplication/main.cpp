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

    // The GUI doesn't have buttons yet, so we'll have to manually start the backend
    // TODO

    // Start the application
    return app.exec();
}
