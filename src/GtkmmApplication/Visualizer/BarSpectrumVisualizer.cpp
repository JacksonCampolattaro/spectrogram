//
// Created by jackcamp on 12/16/20.
//

#include "BarSpectrumVisualizer.h"

BarSpectrumVisualizer::BarSpectrumVisualizer() : GtkmmVisualizer(),
                                                 _box(Gtk::Orientation::ORIENTATION_VERTICAL),
                                                 _bars() {

    this->add(_box);
    _box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    _box.show();

    for (int frequency = 30; frequency < 10000; frequency *= 1.04) {

        _bars.emplace(frequency, Gtk::LevelBar());
        auto &bar = _bars.at(frequency);

        bar.set_max_value(90.0f);
        bar.set_min_value(0.0f);
        bar.set_orientation(Gtk::ORIENTATION_VERTICAL);
        bar.set_inverted();

        bar.remove_offset_value("low");
        bar.remove_offset_value("high");
        bar.remove_offset_value("full");

        _box.pack_start(bar);
        bar.show();
    }

}

void BarSpectrumVisualizer::drawFrequencies(const Fourier::FrequencyDomainBuffer &buffer) {

    for (auto &pair : _bars) {
        auto frame = buffer.at((double) pair.first);
        auto value = frame[0];
        pair.second.set_value(value + 90.0);
    }
}
