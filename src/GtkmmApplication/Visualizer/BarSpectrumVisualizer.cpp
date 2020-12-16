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

    for (int frequency = 30; frequency < 10000; frequency *= 1.2) {

        _bars.emplace(frequency, Gtk::LevelBar());
        auto &bar = _bars.at(frequency);

        bar.set_max_value(1.0);
        bar.set_min_value(0.0);
        bar.set_value(0);
        bar.set_orientation(Gtk::ORIENTATION_VERTICAL);
        bar.set_inverted();

        _box.pack_start(bar);
        bar.show();
    }

}

void BarSpectrumVisualizer::drawFrequencies(const Fourier::FrequencyDomainBuffer &buffer) {

    for (auto &pair : _bars) {
        auto frame = buffer.at((double) pair.first);
        auto value = frame[0];
        auto normalized = (90.0f + value) / 90.0f;
        pair.second.set_value(normalized);
    }
    std::cout << std::endl;
}
