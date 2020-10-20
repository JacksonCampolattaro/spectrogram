
#include <Spectrogram/Audio/System/Blocking.h>
#include <Spectrogram/Audio/Backend/Soundio.h>
#include <Spectrogram/Audio/Backend/Dummy.h>

#include <iostream>

#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/textview.h>
#include <gtkmm/scrolledwindow.h>

using namespace Spectrogram::Audio;

int main(int argc, char *argv[]) {

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
    auto system = System::Blocking(std::make_unique<Backend::Soundio>());
    system.start(system.devices()[2], std::chrono::seconds(2));
    Buffer buffer;
    buffer.resize(system.devices()[2].channelCount);
    for (auto &channel : buffer)
        channel.resize(200);
    system.fillBuffer(buffer);
    system.stop();

    // Set the text
    std::stringstream text;
    for (auto sample : buffer[0])
        text << sample << "\n";
    textView.get_buffer()->set_text(text.str());

    // Run the app
    return app->run(window);
}
