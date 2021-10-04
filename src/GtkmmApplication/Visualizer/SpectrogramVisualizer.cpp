//
// Created by jackcamp on 10/4/21.
//

#include "SpectrogramVisualizer.h"

SpectrogramVisualizer::SpectrogramVisualizer() {

    _surface = Cairo::ImageSurface::create(Cairo::FORMAT_RGB24, 512, 1024);

    this->add(_drawingArea);
    _drawingArea.show();
}

void SpectrogramVisualizer::drawFrequencies(const Fourier::FrequencyDomainBuffer &buffer) {
    assert(buffer.numFrames() > 0 && buffer.numChannels() < 4);

    // Create a new surface to draw to
    auto new_surface = Cairo::ImageSurface::create(_surface->get_format(), _surface->get_width(), _surface->get_width());
    auto cr = Cairo::Context::create(new_surface);

    // The new surface should contain everything in the old one, shifted to the left by one pixel
    {
        cr->set_source(_surface, -1, 0);
        cr->paint();
    }

    // Add new information at the end of the surface
    {

        for (int y = 0; y < _surface->get_height(); ++y) {

            auto frequency = inverseLogScale(
                    {0, _surface->get_height()},
                    {20, 15000},
                    _surface->get_height() - y
            );
            std::size_t index = std::floor(frequency * buffer.time());

            auto brightness_right = buffer.channels()[0].at(index);
            auto brightness_left = buffer.channels()[1].at(index);

            cr->set_source_rgb(brightness_right, 0, brightness_left);
            cr->rectangle(_surface->get_width() - 1, y, 10, 1);
            cr->fill();
        }
    }

    // Swap out the surface for the new one
    _surface = new_surface;

    queue_draw();
}

double
SpectrogramVisualizer::inverseLogScale(std::pair<double, double> input_range, std::pair<double, double> output_range,
                                       double input_value) {

    auto &[input_min, input_max] = input_range;
    auto &[output_min, output_max] = output_range;

    auto input_value_normalized = (input_value) / (input_max);

    auto output_value_normalized = std::pow(input_value_normalized, 2);

    return output_min + output_value_normalized * (output_max - output_min);
}

bool SpectrogramVisualizer::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {

    cr->scale((double) get_width() / (double) _surface->get_width(),
              (double) get_height() / (double) _surface->get_height());
    cr->set_source(_surface, 0, 0);
    cr->paint();

    return true;
}
