#include <QApplication>
#include <QtMainApplication/QtAudioSystem.h>
#include "QtApplication.h"


int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	QtApplication gui;
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
