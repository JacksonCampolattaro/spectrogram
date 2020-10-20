
#include "TextSpectrumView.h"
#include "AudioSystem.h"

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

    AudioSystem system(std::make_unique<Backend::Soundio>());
    system.newBuffer.connect(textSpectrumView.on_newBuffer);
    auto device = system.devices()[2];
    system.start(device, std::chrono::seconds(2), device.sampleRate);

    // Run the app
    return app->run(window);
}
