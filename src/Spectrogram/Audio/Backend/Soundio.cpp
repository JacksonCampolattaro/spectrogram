//
// Created by jackcamp on 10/6/20.
//

#include <cassert>
#include <chrono>
#include <thread>
#include "Soundio.h"

typedef struct {
    Spectrogram::Audio::Buffer buffer;
    Spectrogram::Audio::Backend::Backend::NewBufferCallback handler;
} UserData;

static void read_callback(struct SoundIoInStream *instream, int minFrameCount, int maxFrameCount) {
    auto options = static_cast<UserData *>(instream->userdata);
    int err;

    // Make sure we're not falling behind
    assert(maxFrameCount < 20000);

    // The number of frames we need is the gap between the buffer's capacity and its size
    int framesMissing = options->buffer[0].capacity() - options->buffer[0].size();

    // The number of frames we'll request is limited by the maxFrameCount
    auto framesToRequest = std::min(framesMissing, maxFrameCount);

    while (framesToRequest > 0)
    {

        auto frameCount = framesToRequest;

        // Request those frames
        struct SoundIoChannelArea *areas;
        if ((err = soundio_instream_begin_read(instream, &areas, &frameCount))) {
            std::cerr << "Error starting read: " << soundio_strerror(err);
            exit(1);
        }
        framesToRequest -= frameCount;

        // If we didn't get any frames, stop trying to read
        if (!frameCount) return;

        // If we successfully got frames
        if (areas) {

            // Add the new frames to the buffer
            for (int channel = 0; channel < options->buffer.size(); ++channel) {
                auto sampleArray = reinterpret_cast<Spectrogram::Audio::Sample *>(areas[channel].ptr);

                options->buffer[channel].insert(options->buffer[channel].end(), sampleArray, sampleArray + frameCount);
            }
        }

        // Stop reading data
        if ((err = soundio_instream_end_read(instream))) {
            std::cerr << "Error ending read: " << soundio_strerror(err);
            exit(1);
        }
    }

    // If the buffer is full now, we can push it and wipe it
    if (options->buffer[0].size() == options->buffer[0].capacity()) {

        // Send the buffer to the system
        (options->handler)(options->buffer);

        // Remove all the elements of the buffer, but change its capacity
        for (auto &channel : options->buffer)
            channel.resize(0);
    }

}

static void overflow_callback(struct SoundIoInStream *instream) {

    std::cerr << "overflow" << std::endl;
}

Spectrogram::Audio::Backend::Soundio::Soundio() {

    _soundio = soundio_create();
    soundio_connect(_soundio);
    soundio_flush_events(_soundio);

    // Add devices detected at startup
    size_t defaultInput = soundio_default_input_device_index(_soundio);
    for (size_t i = 0; i < soundio_input_device_count(_soundio); ++i) {

        auto deviceInfo = soundio_get_input_device(_soundio, i);
        _devices.emplace_back(deviceInfo->name, i, i == defaultInput);
        soundio_device_unref(deviceInfo);
    }
}

Spectrogram::Audio::DeviceList &Spectrogram::Audio::Backend::Soundio::devices() {

    // TODO This is going to contain some interesting logic for keeping the device list updated
    return _devices;
}

void Spectrogram::Audio::Backend::Soundio::start(const Device &device, size_t frames, NewBufferCallback callback) {

    stop();

    SoundIoDevice *soundioDevice = soundio_get_input_device(_soundio, device.id);

    assert(soundioDevice);
    assert(!soundioDevice->probe_error);

    soundio_device_sort_channel_layouts(soundioDevice);

    // Select a sample rate
    int sampleRate = soundioDevice->sample_rate_current;
    std::cout << "sample rate = " << sampleRate << "\n";

    // Select a format
    enum SoundIoFormat format = SoundIoFormatInvalid;
    format = sampleTypeToFormat<Sample>();
    assert(soundio_device_supports_format(soundioDevice, format));
    std::cout << "format = " << soundio_format_string(format) << "\n";

    // Configure the input stream
    _inStream = soundio_instream_create(soundioDevice);
    assert(_inStream);
    _inStream->sample_rate = sampleRate;
    _inStream->format = format;
    _inStream->layout = soundioDevice->current_layout;
    _inStream->read_callback = read_callback;
    _inStream->overflow_callback = overflow_callback;

    // Set the user data
    auto userData = new UserData{Buffer{}, callback};
    userData->buffer.resize(_inStream->layout.channel_count);
    for (auto &channel : userData->buffer)
        channel.reserve(frames);
    _inStream->userdata = userData;

    int err;
    if ((err = soundio_instream_open(_inStream))) {
        std::cerr << "failed to open input stream: " << soundio_strerror(err) << std::endl;
        exit(1);
    }

    if ((err = soundio_instream_start(_inStream))) {
        std::cerr << "failed to start input stream: " << soundio_strerror(err) << std::endl;
        exit(1);
    }
}

void Spectrogram::Audio::Backend::Soundio::stop() {

    if (_inStream) {

        delete (UserData *) _inStream->userdata;
        soundio_device_unref(_inStream->device);
        soundio_instream_destroy(_inStream);
        _inStream = nullptr;
    }
}
