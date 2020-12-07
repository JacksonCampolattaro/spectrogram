#include "TextSpectrumVisualizer.h"

TextSpectrumVisualizer::TextSpectrumVisualizer() : GtkmmVisualizer() {

    this->add(_scrolledWindow);
    _scrolledWindow.show();

    _scrolledWindow.add(_textView);
    _textView.set_monospace();
    _textView.show();
}

void TextSpectrumVisualizer::drawFrequencies(const Fourier::FrequencyDomainBuffer &buffer) {

    std::stringstream stream;
    for (int frequency = 0;
         frequency < (int) buffer.maxFrequency(); frequency += (int) (1.0 + frequency * 1.01)) {


        stream << frequency << ":\t";
        for (auto intensity : buffer.at(frequency)) {

            float normalizedAmplitude = (90.0f + intensity) / 90.0f;

            stream << "[";

            const int width = 10;
            for (int i = 0; i < width; ++i) {
                stream << ((int) (normalizedAmplitude * width) > i ? '|' : ' ');
            }

            stream << "] ";
        }
        stream << "\n";

    }

    _textView.get_buffer()->set_text(stream.str());
}
