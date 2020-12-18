#include "BarSpectrumVisualizer.h"

BarSpectrumVisualizer::BarSpectrumVisualizer(size_t numBars) : GtkmmVisualizer(),
                                                               _box(Gtk::Orientation::ORIENTATION_VERTICAL),
                                                               _bars(),
                                                               _numBars(numBars) {

    this->add(_box);
    _box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    _box.set_homogeneous();
    _box.show();

    for (size_t i = 0; i < _numBars; ++i) {

        _bars.emplace_back();
        auto &bar = _bars[i];

        bar.set_max_value(1.0f);
        bar.set_min_value(0.0f);
        bar.set_orientation(Gtk::ORIENTATION_VERTICAL);
        bar.set_inverted();

        bar.remove_offset_value("low");
        bar.remove_offset_value("high");
        bar.remove_offset_value("full");

        _box.pack_start(bar);
        bar.show();
    }

    // Make sure all the bars were initialized properly
    assert(_bars.size() == _numBars);
    assert(_box.get_children().size() == _numBars);
}

void BarSpectrumVisualizer::drawFrequencies(const Fourier::FrequencyDomainBuffer &buffer) {

    float minFrequency = 32.0;
    float maxFrequency = buffer.maxFrequency();

    for (size_t i = 0; i < _numBars; ++i) {

        auto f0 = ((float) i / (float) _numBars) * (maxFrequency - minFrequency) + minFrequency;
        auto f1 = ((float) (i + 1) / (float) _numBars) * (maxFrequency - minFrequency) + minFrequency;

        auto rangeStart = logScale(minFrequency, maxFrequency, f0);
        auto rangeEnd = logScale(minFrequency, maxFrequency, f1);

        std::cout << "(" << rangeStart << ", " << rangeEnd << ") " << std::endl;

        auto &bar = _bars[i];

        auto value = buffer.at(rangeStart, rangeEnd)[0];

        bar.set_value(value);
    }
}

double BarSpectrumVisualizer::logScale(double min, double max, double value) {

    return pow(2, ((value - min) / (max - min)) * (log2(max) - log2(min)) + log2(min));
}
