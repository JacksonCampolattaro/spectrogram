//
// Created by jackcamp on 10/6/20.
//

#include <cassert>
#include <chrono>
#include <thread>
#include "Soundio.h"

typedef struct {
    Spectrogram::Audio::Backend::Backend::NewSamplesCallback newSamplesCallback;
    std::vector<Spectrogram::Audio::Sample> sampleArray;
} UserData;

static void read_callback(struct SoundIoInStream *instream, [[maybe_unused]] int minFrameCount, int maxFrameCount) {
    auto userData = static_cast<UserData *>(instream->userdata);
    auto &sampleArrays = userData->sampleArray;
    auto callback = userData->newSamplesCallback;
    int err;

    // This prevents the latency from building up too much
    assert(maxFrameCount < 20000);

    int framesToRead = maxFrameCount;

    // Loop until we've consumed all the frames
    while (framesToRead > 0) {

        // Try to read as many frames as we're allowed to
        int framesRead = framesToRead;
        struct SoundIoChannelArea *areas;
        if ((err = soundio_instream_begin_read(instream, &areas, &framesRead))) {
            std::cerr << "Error starting read: " << soundio_strerror(err);
            exit(1);
        }

        // If we didn't get any frames, stop trying to read (it's also not necessary to close the stream)
        if (framesRead == 0) return;

        // If the read was successful, push the data
        if (areas) {

            for (int frame = 0; frame < framesRead; ++frame) {

                for (size_t channel = 0; channel < sampleArrays.size(); ++channel) {

                    sampleArrays[channel] = *reinterpret_cast<Spectrogram::Audio::Sample *>(areas[channel].ptr);
                    areas[channel].ptr += areas[channel].step;

                }
                callback(&sampleArrays);
            }
        }

        // Update the number of remaining frames
        framesToRead -= framesRead;

        // Stop reading data
        if ((err = soundio_instream_end_read(instream))) {
            std::cerr << "Error ending read: " << soundio_strerror(err);
            exit(1);
        }

    }

    callback(nullptr);
}

static void overflow_callback([[maybe_unused]] struct SoundIoInStream *instream) {

    std::cerr << "overflow" << std::endl;
}

Spectrogram::Audio::Backend::Soundio::Soundio() {

    _soundio = soundio_create();
    soundio_connect(_soundio);
    soundio_flush_events(_soundio);

    // Add devices detected at startup
    int defaultInput = soundio_default_input_device_index(_soundio);
    for (int i = 0; i < soundio_input_device_count(_soundio); ++i) {

        auto deviceInfo = soundio_get_input_device(_soundio, i);
        _devices.push_back(
                {deviceInfo->name, i, i == defaultInput,
                 (size_t) deviceInfo->current_layout.channel_count,
                 (size_t) deviceInfo->sample_rate_current
                }
        );
        soundio_device_unref(deviceInfo);
    }

    _inStream = nullptr;
}

Spectrogram::Audio::DeviceList &Spectrogram::Audio::Backend::Soundio::devices() {

    // TODO This is going to contain some interesting logic for keeping the device list updated
    return _devices;
}

void Spectrogram::Audio::Backend::Soundio::start(const Device &device, NewSamplesCallback callback) {

    // Retrieve the relevant device
    SoundIoDevice *soundioDevice = soundio_get_input_device(_soundio, device.id);
    assert(soundioDevice);
    assert(!soundioDevice->probe_error);

    soundio_device_sort_channel_layouts(soundioDevice);

    // Select a sample rate
    int sampleRate = soundioDevice->sample_rate_current;

    // Select a format
    auto format = sampleTypeToFormat<Sample>();
    assert(soundio_device_supports_format(soundioDevice, format));

    // Configure the input stream
    _inStream = soundio_instream_create(soundioDevice);
    assert(_inStream);
    _inStream->sample_rate = sampleRate;
    _inStream->format = format;
    _inStream->layout = soundioDevice->current_layout;
    _inStream->read_callback = read_callback;
    _inStream->overflow_callback = overflow_callback;

    auto userData = new UserData;
    userData->newSamplesCallback = callback;
    userData->sampleArray.resize(_inStream->layout.channel_count);
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

//        delete (UserData *) _inStream->userdata;
        soundio_device_unref(_inStream->device);
        soundio_instream_destroy(_inStream);
        _inStream = nullptr;
    }
}
