#ifndef SPECTROGRAM_QTAUDIOSYSTEM_H
#define SPECTROGRAM_QTAUDIOSYSTEM_H

#include <Spectrogram/Audio/System/Event.h>

#include <QObject>

using namespace Spectrogram::Audio;

class QtAudioSystem : public System::Event, public QObject {
Q_OBJECT

public:

    QtAudioSystem(std::unique_ptr<Backend::Backend> backend);

    using Event::devices;

public slots:

    void startSlot(const Device &, std::chrono::milliseconds, size_t);

    void stopSlot();

signals:

    void newBufferSignal(const Buffer &buffer);

private:

    void notifyNewData() override;

    void processNewData(const Buffer &buffer) override;

signals:

    void newDataSignal();
};


#endif //SPECTROGRAM_QTAUDIOSYSTEM_H
