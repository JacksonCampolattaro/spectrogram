
#include "AudioSystem.h"
#include "Visualizer/TextSpectrumVisualizer.h"

#include <gtkmm/application.h>
#include <gtkmm/window.h>

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
    TextSpectrumVisualizer textSpectrumVisualizer;
    window.add(textSpectrumVisualizer);
    textSpectrumVisualizer.show();
//    TextSpectrumView textSpectrumView;
//    window.add(textSpectrumView);
//    textSpectrumView.show();
//
//    // Create an audio system to get data from
//    AudioSystem system(std::make_unique<Backend::Soundio>());
//
//    // Link the audio system with the window, so it knows when to draw data
//    system.newBuffer.connect(textSpectrumView.on_newBuffer);
//    textSpectrumView.start.connect(system.start);
//    textSpectrumView.stop.connect(system.stop);
//
//    // Tell the UI what devices are available
//    textSpectrumView.setDevices(system.devices());

    // Run the app
    return app->run(window);
}
