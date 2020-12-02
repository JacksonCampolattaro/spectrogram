
#include <fstream>

#include <QApplication>
#include <QStyleHints>
#include <QScreen>
#include <QWidget>

#include <Spectrogram/Audio/Backend/Dummy.h>
#include <Spectrogram/Audio/Backend/Soundio.h>

#include <QtApplication/QtAudioSystem.h>

#include "QtApplication.h"


int main(int argc, char *argv[]) {

    auto configPath = "spectrogram.rc";

    // Create a default settings profile
    Settings::Profile settings;

    // Attempt to open the config file in the default location
    std::ifstream configFile(configPath);
    if (!configFile) {
        configFile.close();

        // Missing config file, create one
        std::ofstream newConfig(configPath);
        newConfig << settings;
        newConfig.close();
    } else {

        // Load settings from the config file
        configFile >> settings;
    }

    QApplication app(argc, argv);

    QtApplication gui;
	
	QGuiApplication::setApplicationDisplayName(
		QtApplication::tr("Audio Spectrogram Application"));

    gui.applySettingsProfile(settings);
    
    gui.show();

    QtAudioSystem audioSystem(std::make_unique<Backend::Soundio>());
    gui.updateSources(audioSystem.devices()); // Manually tell the gui what devices are available
    QObject::connect(&gui, &QtApplication::startSignal,
                     &audioSystem, &QtAudioSystem::startSlot);
    QObject::connect(&gui, &QtApplication::stopSignal,
                     &audioSystem, &QtAudioSystem::stopSlot);

    QObject::connect(&audioSystem, &QtAudioSystem::newBufferSignal,
                     &gui, &QtApplication::updateSpectrogram);

    return app.exec();
}
