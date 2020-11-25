#include <catch2/catch.hpp>

#include <Spectrogram/Settings/Profile.h>
#include <iostream>

TEST_CASE("Saving and loading settings profiles", "[Settings]") {

    Settings::Profile profile{};

    profile.colorScheme = 5;

    std::stringstream stream{};

    stream << profile;

    std::cout << stream.str();

    Settings::Profile newProfile{};

    stream >> newProfile;

    CHECK(newProfile.colorScheme == 5);
}

