#include <catch2/catch.hpp>

#include <Spectrogram/Fourier/processor.h>
#include <iostream>

TEST_CASE("Doing sample transforms", "[Fourier::process]") {

    float testSamples[5] = {1,2,3,4,5};
    Fourier::Processor processor(5); 
    std::vector<float> processedWindow = processor.compute(testSamples);
    std::cout << "\nuh here ya go:\n";
    for(float d : processedWindow)
        std::cout << d << ", ";
    std::cout << std::endl;
}
