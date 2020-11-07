#include "QtAudioSystem.h"

QtAudioSystem::QtAudioSystem(std::unique_ptr<Backend::Backend> backend) :
        QObject(),
        Event(std::move(backend)) {

    // TODO: Internal signals should be linked up here
}

void QtAudioSystem::startSlot(const Device &device, std::chrono::milliseconds maxLatency, size_t bufferLength) {
    Event::start(device, maxLatency, bufferLength);
}

void QtAudioSystem::stopSlot() {
    Event::stop();
}

void QtAudioSystem::notifyNewData() {
    newDataSignal();
}

void QtAudioSystem::processNewData(const Buffer &buffer) {
    newBufferSignal(buffer);
}
