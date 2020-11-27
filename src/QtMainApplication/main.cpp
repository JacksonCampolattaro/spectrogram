#include <QApplication>
#include <Spectrogram/Visualizer/QtAudioSystem.h>
#include "QtMainApplication.h"


int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	QtMainApplication gui;
	gui.show();

	QtAudioSystem audioSystem(std::make_unique<Backend::Soundio>());
	gui.updateSources(audioSystem.devices()); // Manually tell the gui what devices are available
	QObject::connect(&gui, &QtMainApplication::startSignal,
                     &audioSystem, &QtAudioSystem::startSlot);
	QObject::connect(&gui, &QtMainApplication::stopSignal,
                     &audioSystem, &QtAudioSystem::stopSlot);

	QObject::connect(&audioSystem, &QtAudioSystem::newBufferSignal,
                     &gui, &QtMainApplication::updateSpectrogram);

	return app.exec();
}
