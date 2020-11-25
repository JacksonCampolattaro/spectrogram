
#ifndef SPECTROGRAM_PROFILE_H
#define SPECTROGRAM_PROFILE_H

#include <Spectrogram/Settings/Settings.h>

#include <toml.hpp>

#include <istream>
#include <ostream>

namespace Settings {

    class Profile {
    public:

        int colorScheme;


        friend std::ostream &operator<<(std::ostream &out, const Settings::Profile &p) {

            const toml::value data{
                {"colorscheme", p.colorScheme}
            };

            out << data;

            return out;
        }

        friend std::istream &operator>>(std::istream &in, Settings::Profile &p) {

            auto data = toml::parse(in);

            p.colorScheme = toml::find<int>(data, "colorscheme");

            return in;
        }
    };

}

#endif //SPECTROGRAM_PROFILE_H
