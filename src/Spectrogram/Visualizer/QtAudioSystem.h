#ifndef SPECTROGRAM_QTAUDIOSYSTEM_H
#define SPECTROGRAM_QTAUDIOSYSTEM_H

#include <Spectrogram/Audio/System/Event.h>

#include <QObject>

using namespace Spectrogram::Audio;

class QtAudioSystem : public QObject, public Spectrogram::Audio::System::Event {
Q_OBJECT

public:

    QtAudioSystem(std::unique_ptr<Backend::Backend> backend);

    using Event::devices;

public slots:

    void startSlot(const Device &device, std::chrono::milliseconds maxLatency, size_t bufferLength);

    void stopSlot();

signals:

    void newBufferSignal(const Buffer &buffer);

private:

    void notifyNewData() override;

    void processNewData(const Buffer &buffer) override;

private slots:

    void newDataSlot();

signals:

    void newDataSignal();
};


#endif //SPECTROGRAM_QTAUDIOSYSTEM_H
