
#include <Spectrogram/Audio/System/Blocking.h>
#include <Spectrogram/Audio/Backend/Soundio.h>
#include <Spectrogram/Audio/Backend/Dummy.h>

#include <Spectrogram/Fourier/processor.h>

#include <iostream>

#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/textview.h>
#include <gtkmm/scrolledwindow.h>

using namespace Spectrogram::Audio;
using namespace Spectrogram::Fourier;

int main(int argc, char *argv[]) {

    const size_t bufferSize = 48000;
    const size_t deviceNumber = 0;

    // Create an app
    auto app = Gtk::Application::create(argc, argv, "spectrogram.gtk");

    // Create a window with a textview
    Gtk::Window window;
    Gtk::ScrolledWindow scrolledWindow;
    Gtk::TextView textView;
    textView.set_editable(false);
    window.add(scrolledWindow);
    scrolledWindow.add(textView);
    window.show_all_children();

    // Read data from an audio stream
    auto system = System::Blocking(std::make_unique<Backend::Dummy>(100));
    system.start(system.devices()[deviceNumber], std::chrono::seconds(2));
    Buffer buffer;
    buffer.resize(system.devices()[deviceNumber].channelCount);
    for (auto &channel : buffer)
        channel.resize(bufferSize);
    system.fillBuffer(buffer);
    system.stop();

    // Use a processor to convert that data to the time domain
    Processor processor(bufferSize);
    auto timeDomainResult = processor.compute(buffer[0]);

    // Set the text
    std::stringstream text;
    for (size_t i = 0; i < bufferSize / 2; ++i) {
        text << i << ": " << timeDomainResult[i] << "\n";
    }
    textView.get_buffer()->set_text(text.str());

    // Run the app
    return app->run(window);
}
