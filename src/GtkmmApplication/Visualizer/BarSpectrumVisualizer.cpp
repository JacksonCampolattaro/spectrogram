#include "BarSpectrumVisualizer.h"

BarSpectrumVisualizer::BarSpectrumVisualizer(size_t numBars) : GtkmmVisualizer(),
                                                               _box(Gtk::Orientation::ORIENTATION_VERTICAL),
                                                               _bars(),
                                                               _numBars(numBars) {

    this->add(_box);
    _box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    _box.show();

    for (size_t i = 0; i < _numBars; ++i) {

        _bars.emplace_back();
        auto &bar = _bars[i];

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

    for (size_t i = 0; i < _numBars; ++i) {

        double minFrequency = logScale(0, buffer.maxFrequency(), i * buffer.maxFrequency());
        double maxFrequency = logScale(0, buffer.maxFrequency(), (i + 1.0) * buffer.maxFrequency());

        auto &bar = _bars[i];

        auto value = buffer.at(minFrequency, maxFrequency)[0];

        bar.set_value(value + 90.0);
    }
}

double BarSpectrumVisualizer::logScale(double min, double max, double value) {
    auto normalized = (value - min) / (min - max);
    return log2(normalized) * (max - min) + min;
}
