
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
    window.set_default_size(200, 500);
    window.set_title("Spectrogram");
    TextSpectrumView textSpectrumView;
    window.add(textSpectrumView);
    textSpectrumView.show();

    // Create an audio system to get data from
    AudioSystem system(std::make_unique<Backend::Soundio>());

    // Link the audio system with the window, so it knows when to draw data
    system.newBuffer.connect(textSpectrumView.on_newBuffer);

    // Tell the UI what devices are available
    textSpectrumView.setDevices(system.devices());

    // Start the audio system
//    auto device = system.devices()[2];
//    std::cout << "device = " << device << "\n";
//    system.start(device, std::chrono::seconds(2), device.sampleRate/60);

    // Run the app
    return app->run(window);
}
