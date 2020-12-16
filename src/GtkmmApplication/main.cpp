
#include "AudioSystem.h"
#include "Visualizer/TextSpectrumVisualizer.h"
#include "Visualizer/BarSpectrumVisualizer.h"

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
    window.set_default_size(300, 300);
    window.set_title("Spectrogram");
    BarSpectrumVisualizer visualizer{100};
    window.add(visualizer);
    visualizer.show();

    AudioSystem system(std::make_unique<Backend::Soundio>());

    system.newBuffer.connect(visualizer.slot_draw);

    const auto &device = system.devices()[1];
    std::cout << device << std::endl;
    system.start(device, std::chrono::seconds(1), device.sampleRate / 3);

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
