
#ifndef SPECTROGRAM_PROFILE_H
#define SPECTROGRAM_PROFILE_H

#include <Spectrogram/Settings/Settings.h>

#include <toml.hpp>

#include <istream>
#include <ostream>

namespace Settings {

    class Profile {
    public:

        int colorScheme = 0;
        bool logscale = true;

        friend std::ostream &operator<<(std::ostream &out, const Settings::Profile &p) {

            const toml::value data{
                {"colorscheme", p._colorSchemeNames[p.colorScheme]},
                {"logscale", p.logscale}
            };

            out << data;

            return out;
        }

        friend std::istream &operator>>(std::istream &in, Settings::Profile &p) {

            auto data = toml::parse(in);

            std::string colorSchemeName = toml::find<std::string>(data, "colorscheme");
            p.colorScheme = std::find(p._colorSchemeNames.begin(), p._colorSchemeNames.end(), colorSchemeName) - p._colorSchemeNames.begin();

            p.logscale = toml::find<bool>(data, "logscale");

            return in;
        }

    private:

        std::vector<std::string> _colorSchemeNames = {
                "grayscale",
                "hot",
                "cold",
                "night",
                "candy",
                "geography",
                "ion",
                "thermal",
                "polar",
                "spectrum",
                "jet",
                "hues"
        };
    };

}

#endif //SPECTROGRAM_PROFILE_H
