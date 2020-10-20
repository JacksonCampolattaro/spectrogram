
#include "TextSpectrumView.h"

#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/textview.h>

#include <Spectrogram/Audio/System/Blocking.h>
#include <Spectrogram/Audio/Backend/Soundio.h>
#include <Spectrogram/Audio/Backend/Dummy.h>

using namespace Spectrogram::Audio;
using namespace Spectrogram::Fourier;

int main(int argc, char *argv[]) {

    // Create an app
    auto app = Gtk::Application::create(argc, argv, "spectrogram.gtk");

    // Create a window with a TextSpectrumView
    Gtk::Window window;
    TextSpectrumView textSpectrumView;
    window.add(textSpectrumView);
    textSpectrumView.show();


//    auto system = Audio::System::Blocking(std::make_unique<Audio::Backend::Soundio>());
    auto system = Audio::System::Blocking(std::make_unique<Audio::Backend::Dummy>(100));

    // Choose a device
    auto device = system.devices()[2];

    // Create a buffer to hold data from that device
    Audio::Buffer buffer;
    buffer.resize(device.channelCount);
    for (auto &channel : buffer)
        // Make room for exactly one second of audio
        channel.resize(device.sampleRate);

    // Read data from the device
    system.start(device, std::chrono::seconds(2));
    system.fillBuffer(buffer);
    system.stop();

    textSpectrumView.drawBuffer(buffer);

    // Run the app
    return app->run(window);
}
