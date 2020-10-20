
#include <Spectrogram/Audio/System/Blocking.h>
#include <Spectrogram/Audio/Backend/Soundio.h>
#include <Spectrogram/Audio/Backend/Dummy.h>

#include <gtkmm/application.h>
#include <gtkmm/window.h>

#include <iostream>

using namespace Spectrogram::Audio;

int main(int argc, char *argv[]) {

    auto app = Gtk::Application::create(argc, argv, "spectrogram.gtk");

    Gtk::Window window;

    return app->run(window);
}
