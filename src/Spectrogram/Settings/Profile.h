
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

        friend std::ostream & operator << (std::ostream &out, const Profile &p);
        friend std::istream & operator >> (std::istream &in,  Profile &p);
    };

}

#endif //SPECTROGRAM_PROFILE_H
