#include <catch2/catch.hpp>

#include <Fourier/fourier.h>

TEST_CASE("Doing sample transforms", "[Fourier::process]") {

    double testSamples[5] = {1,2,3,4,5};
    Fourier::process(testSamples, 5);
}
