//
// Created by jackcamp on 10/6/20.
//

#include <cassert>
#include "Soundio.h"

static void read_callback(struct SoundIoInStream *instream, int minFrameCount, int maxFrameCount) {

    //std::cout << maxFrameCount << std::endl;

    auto callback = static_cast<Spectrogram::Audio::Backend::Backend::NewBufferCallback *>(instream->userdata);

    int err;

    struct SoundIoChannelArea *areas;
    int frames = 500;

    err = soundio_instream_begin_read(instream, &areas, &frames);
    if (err) exit(1);
    assert(areas);
    assert(frames);

    Spectrogram::Audio::Buffer buffer;

//    buffer.assign((Spectrogram::Audio::Sample *) areas[0].ptr, ((Spectrogram::Audio::Sample *) areas[0].ptr) + frames);
    for (int channel = 0; channel < instream->layout.channel_count; ++channel) {

        buffer.emplace_back((Spectrogram::Audio::Sample *) areas[channel].ptr,
                               ((Spectrogram::Audio::Sample *) areas[channel].ptr) + frames);
    }

    (*callback)(buffer);

    err = soundio_instream_end_read(instream);
    if (err) exit(1);
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

void Spectrogram::Audio::Backend::Soundio::start(const Spectrogram::Audio::Device &device,
                                                 Spectrogram::Audio::Backend::Backend::NewBufferCallback callback) {

    stop();

    _callback = callback;

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
    _inStream->userdata = &_callback;

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

        soundio_device_unref(_inStream->device);
        soundio_instream_destroy(_inStream);
        _inStream = nullptr;
    }
}
