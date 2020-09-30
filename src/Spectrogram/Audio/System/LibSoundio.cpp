#include <cassert>
#include <zconf.h>
#include "LibSoundio.h"

static void read_callback(struct SoundIoInStream *instream, int minFrameCount, int maxFrameCount) {

    //std::cout << "read callback invoked" << std::endl;

    struct SoundIoChannelArea *areas;
    int frames = 1000;

    soundio_instream_begin_read(instream, &areas, &frames);
    assert(areas);
    assert(frames);

    for (int frame = 0; frame < frames; ++frame) {

        for (int channel = 0; channel < instream->layout.channel_count; ++channel) {

            float sample = *((float *) (areas[channel].ptr + (areas[channel].step * frame)));
            std::cout << sample << "\t";
        }
        std::cout << "\n";
    }

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
    for (auto device : getDevices()) {
        if (!device.isInput && device.isDefault) {
            setDevice(device);
            break;
        }
    }

}

Spectrogram::Audio::System::LibSoundio::~LibSoundio() {

    soundio_destroy(_soundio);
}

void Spectrogram::Audio::System::LibSoundio::setBufferSize(size_t size) {

}

Spectrogram::Audio::Buffer Spectrogram::Audio::System::LibSoundio::getBuffer() {
    soundio_flush_events(_soundio);

    return Spectrogram::Audio::Buffer();
}

std::vector<Spectrogram::Audio::Device> Spectrogram::Audio::System::LibSoundio::getDevices() {

    std::vector<Device> devices;

    size_t defaultOutput = soundio_default_output_device_index(_soundio);
    for (size_t i = 0; i < soundio_output_device_count(_soundio); ++i) {

        auto deviceInfo = soundio_get_output_device(_soundio, i);
        devices.emplace_back(deviceInfo->name, i, i == defaultOutput, false);
    }

    size_t defaultInput = soundio_default_input_device_index(_soundio);
    for (size_t i = 0; i < soundio_input_device_count(_soundio); ++i) {

        auto deviceInfo = soundio_get_input_device(_soundio, i);
        devices.emplace_back(deviceInfo->name, i, i == defaultInput, true);
    }
    return devices;
}

void Spectrogram::Audio::System::LibSoundio::setDevice(Spectrogram::Audio::Device &device) {

    std::cout << "Setting device...";

    auto soundioDevice = soundio_get_input_device(_soundio, device.id);
    assert(soundioDevice);
    assert(!soundioDevice->probe_error);
    soundio_device_sort_channel_layouts(soundioDevice);

    // Select a sample rate
    int sampleRate = 0;
    for (auto option : _prioritizedSampleRates) {

        if (soundio_device_supports_sample_rate(soundioDevice, option)) {

            sampleRate = option;
            break;
        }
    }
    assert(sampleRate);

    // Select a format
    enum SoundIoFormat format = SoundIoFormatInvalid;
    for (auto option : _prioritizedAudioFormats) {

        if (soundio_device_supports_format(soundioDevice, option)) {

            format = option;
            break;
        }
    }
    assert(SoundIoFormatInvalid != format);

    // Configure the input stream
    _inStream = soundio_instream_create(soundioDevice);
    assert(_inStream);
    _inStream->sample_rate = sampleRate;
    _inStream->format = format;
    _inStream->read_callback = read_callback;
    _inStream->overflow_callback = overflow_callback;



    int err;
    if ((err = soundio_instream_open(_inStream))) {
        std::cerr << "error" << std::endl;
    }
    if ((err = soundio_instream_start(_inStream))) {
        std::cerr << "error" << std::endl;
    }


    // TODO
    std::cout << " Done" << std::endl;
}
