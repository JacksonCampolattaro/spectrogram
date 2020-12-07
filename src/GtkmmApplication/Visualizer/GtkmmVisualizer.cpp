#include "GtkmmVisualizer.h"

GtkmmVisualizer::GtkmmVisualizer() {
    slot_draw = sigc::mem_fun(*this, &GtkmmVisualizer::draw);
}

void GtkmmVisualizer::draw(const Audio::Buffer &buffer) {
    std::cout << "Drawing new data!" << std::endl;
    for (const auto &channel : buffer.channels())
        std::cout << channel[0] << std::endl;
}
