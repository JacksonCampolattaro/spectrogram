
#include "TextSpectrumView.h"

#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/textview.h>


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

    // Run the app
    return app->run(window);
}
