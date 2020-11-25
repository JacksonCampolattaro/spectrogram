#include "Profile.h"

std::ostream &operator<<(std::ostream &out, const Settings::Profile &p) {

    out << p.colorScheme;
    return out;
}

std::istream &operator>>(std::istream &in, Settings::Profile &p) {

    auto data = toml::parse(in);

    p.colorScheme = toml::find<int>(data, "colorscheme");

    return in;
}
