//
// Created by jackcamp on 10/11/20.
//

#include "MonolithicSystem.h"

static void read_callback(struct SoundIoInStream *instream, int minFrameCount, int maxFrameCount) {

    auto queues = reinterpret_cast<Spectrogram::Audio::MonolithicSystem::ChannelQueues *>(instream->userdata);
    assert(queues);
    int err = 0;

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

            for (size_t channel = 0; channel < queues->size(); ++channel) {

                auto sampleArray = reinterpret_cast<Spectrogram::Audio::Sample *>(areas[channel].ptr);

                auto samplesWritten = (*queues)[channel]->push(sampleArray, sampleArray + framesRead);
                assert(samplesWritten == framesRead);

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
}

static void overflow_callback(struct SoundIoInStream *instream) {

    assert(false);
}

Spectrogram::Audio::MonolithicSystem::MonolithicSystem() {

    _soundio = soundio_create();
    soundio_connect(_soundio);
    soundio_flush_events(_soundio);

    // Add devices detected at startup
    int defaultInput = soundio_default_input_device_index(_soundio);
    for (int i = 0; i < soundio_input_device_count(_soundio); ++i) {

        auto deviceInfo = soundio_get_input_device(_soundio, i);
        _devices.emplace_back(deviceInfo->name, i, i == defaultInput);
        soundio_device_unref(deviceInfo);
    }

//    _channelQueues.push_back(boost::lockfree::spsc_queue<Sample, boost::lockfree::capacity<1024>>());
}

Spectrogram::Audio::DeviceList &Spectrogram::Audio::MonolithicSystem::devices() {

    return _devices;
}

void Spectrogram::Audio::MonolithicSystem::start(const Spectrogram::Audio::Device &device) {

    // Retrieve the relevant device
    SoundIoDevice *soundioDevice = soundio_get_input_device(_soundio, device.id);
    assert(soundioDevice);
    assert(!soundioDevice->probe_error);

    soundio_device_sort_channel_layouts(soundioDevice);

    // Select a sample rate
    int sampleRate = soundioDevice->sample_rate_current;
    std::cout << "sample rate = " << sampleRate << "\n";

    // Select a format
    auto format = sampleTypeToFormat<Sample>();
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

    _channelQueues.clear();
    for (int channel = 0; channel < _inStream->layout.channel_count; ++channel) {
        _channelQueues.push_back(std::make_unique<ChannelQueue>(10 * 44100));
    }
    _inStream->userdata = &_channelQueues;

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

Spectrogram::Audio::Buffer Spectrogram::Audio::MonolithicSystem::getBuffer(size_t frames) {

    Spectrogram::Audio::Buffer buffer;
    buffer.resize(_channelQueues.size());

    for (size_t frame = 0; frame < frames; ++frame) {
        for (size_t channel = 0; channel < buffer.size(); ++channel) {

            while (_channelQueues[channel]->read_available() < frames) {}

            buffer[channel].push_back(_channelQueues[channel]->front());
            _channelQueues[channel]->pop();
        }
    }

    return buffer;
}

void Spectrogram::Audio::MonolithicSystem::stop() {

}
