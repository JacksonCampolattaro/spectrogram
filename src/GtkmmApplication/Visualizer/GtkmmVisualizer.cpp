#include "GtkmmVisualizer.h"

GtkmmVisualizer::GtkmmVisualizer() {
    slot_draw = sigc::mem_fun(*this, &Visualizer::draw);
}
