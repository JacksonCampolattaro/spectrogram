#include <cassert>
#include <zconf.h>
#include "LibSoundio.h"

static void read_callback(struct SoundIoInStream *instream, int minFrameCount, int maxFrameCount) {

    //std::cout << "read callback invoked" << std::endl;
    int err;

    struct SoundIoChannelArea *areas;
    int frames = 10000;

    err = soundio_instream_begin_read(instream, &areas, &frames);
    if (err) exit(1);
    assert(areas);
    assert(frames);

    for (int frame = 0; frame < frames; ++frame) {

        for (int channel = 0; channel < instream->layout.channel_count; ++channel) {

            int16_t sample = *((int16_t *) areas[channel].ptr);
            areas[channel].ptr += areas[channel].step;
            std::cout << sample << "\t";
        }
        std::cout << "\n";
    }

    err = soundio_instream_end_read(instream);
    if (err) exit(1);

    std::cout << "\n\n";
}

static void overflow_callback(struct SoundIoInStream *instream) {

    std::cerr << "overflow" << std::endl;
}

Spectrogram::Audio::System::LibSoundio::LibSoundio() {

    // Configure soundio
    _soundio = soundio_create();
    soundio_connect(_soundio);
    soundio_flush_events(_soundio);

    // Connect to the default output device
//    for (auto device : getDevices()) {
//        if (!device.isInput && device.isDefault) {
//            setDevice(device);
//            break;
//        }
//    }

}

Spectrogram::Audio::System::LibSoundio::~LibSoundio() {

    soundio_destroy(_soundio);
}

void Spectrogram::Audio::System::LibSoundio::setBufferSize(size_t size) {

}

Spectrogram::Audio::Buffer Spectrogram::Audio::System::LibSoundio::getBuffer() {

    soundio_wait_events(_soundio);
    std::cout << std::flush;
    return Spectrogram::Audio::Buffer();
}

std::vector<Spectrogram::Audio::Device> Spectrogram::Audio::System::LibSoundio::getDevices() {

    std::vector<Device> devices;

    soundio_flush_events(_soundio);

    size_t defaultOutput = soundio_default_output_device_index(_soundio);
    for (size_t i = 0; i < soundio_output_device_count(_soundio); ++i) {

        auto deviceInfo = soundio_get_output_device(_soundio, i);
        assert(!deviceInfo->probe_error);
        devices.emplace_back(deviceInfo->name, i, i == defaultOutput, false);
        soundio_device_unref(deviceInfo);
    }

    size_t defaultInput = soundio_default_input_device_index(_soundio);
    for (size_t i = 0; i < soundio_input_device_count(_soundio); ++i) {

        auto deviceInfo = soundio_get_input_device(_soundio, i);
        devices.emplace_back(deviceInfo->name, i, i == defaultInput, true);
        soundio_device_unref(deviceInfo);
    }
    return devices;
}

void Spectrogram::Audio::System::LibSoundio::setDevice(Spectrogram::Audio::Device &device) {

    std::cout << "Setting device...\n";

    SoundIoDevice *soundioDevice = nullptr;
    if (device.isInput)
        soundioDevice = soundio_get_input_device(_soundio, device.id);
    else
        soundioDevice = soundio_get_output_device(_soundio, device.id);

    assert(soundioDevice);
    assert(!soundioDevice->probe_error);

    soundio_device_sort_channel_layouts(soundioDevice);

    // Select a sample rate
    int sampleRate = soundioDevice->sample_rates[0].min;
    assert(sampleRate);
    std::cout << "sample rate = " << sampleRate << "\n";

    // Select a format
    enum SoundIoFormat format = SoundIoFormatInvalid;
//    for (auto option : _prioritizedAudioFormats) {
//
//        if (soundio_device_supports_format(soundioDevice, option)) {
//
//            format = option;
//            break;
//        }
//    }
//    assert(SoundIoFormatInvalid != format);
    format = SoundIoFormatS16LE;
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

    int err;
    if ((err = soundio_instream_open(_inStream))) {
        std::cerr << "failed to open input stream: " << soundio_strerror(err) << std::endl;
        exit(1);
    }

    if ((err = soundio_instream_start(_inStream))) {
        std::cerr << "failed to start input stream: " << soundio_strerror(err) << std::endl;
        exit(1);
    }

    // TODO
    std::cout << "Done" << std::endl;
}
