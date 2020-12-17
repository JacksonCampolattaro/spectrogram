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

    float minFrequency = 32.0;
    float maxFrequency = buffer.maxFrequency() - 1;

    for (size_t i = 0; i < _numBars; ++i) {

        auto f0 = ((float) i / (float) _numBars) * (maxFrequency - minFrequency) + minFrequency;
        auto f1 = ((float) (i + 1) / (float) _numBars) * (maxFrequency - minFrequency) + minFrequency;

        auto rangeStart = logScale(minFrequency, buffer.maxFrequency(), f0);
        auto rangeEnd = logScale(minFrequency, buffer.maxFrequency(), f1);

        auto &bar = _bars[i];

        auto value = buffer.at(rangeStart, rangeEnd)[0];

        bar.set_value(value + 90.0);
    }

    std::cout << std::endl;
}

double BarSpectrumVisualizer::logScale(double min, double max, double value) {

    return pow(2, ((value - min) / (max - min)) * (log2(max) - log2(min)) + log2(min));
}
