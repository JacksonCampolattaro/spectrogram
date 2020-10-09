#include <catch2/catch.hpp>

#include <Spectrogram/Fourier/processor.h>
#include <iostream>
#include <vector>

using namespace Spectrogram::Fourier;

TEST_CASE("Test constructors", "[Processor]") {

    Processor a(5); 
    REQUIRE(a.getSampleSize() == 5);
    REQUIRE(a.getOutputSize() == 3);
    

    Processor b;
    a = b;
    REQUIRE(b.getSampleSize() == 2048);
    REQUIRE(b.getOutputSize() == 1025);
    REQUIRE(a.getSampleSize() == 2048);
    REQUIRE(a.getOutputSize() == 1025);

    Processor c(a); 
    REQUIRE(c.getSampleSize() == 2048);
    REQUIRE(c.getOutputSize() == 1025);

    REQUIRE_THROWS_AS(Processor(0), std::invalid_argument);

}

TEST_CASE("Test setters", "[Processor]") {
    Processor a(1024);
    REQUIRE(a.getSampleSize() == 1024);
    REQUIRE(a.getOutputSize() == 513);

    a.setSampleSize(16384);
    REQUIRE(a.getSampleSize() == 16384);
    REQUIRE(a.getOutputSize() == 8193);

}

TEST_CASE("Test math", "[Processor]") {
    
    int aFreq = 3; // Hz
    int aSampleRate = 100; 
    std::vector<float> aSamples(aSampleRate, 0);

    for (int t = 0; t < aSampleRate; t++)
    {
        aSamples[t] =  sin(2*M_PI*aFreq*((double)t/aSampleRate));
    }

    Processor a(aSampleRate); 
    std::vector<float> aProcessedWindow = a.compute(aSamples);
    std::cout << "freq bin 3 should be 1 since the freq = 3:\n";
    std::cout << "output:\n";
    for(float db : aProcessedWindow)
        std::cout << db << ", ";
    std::cout << std::endl;
    REQUIRE(aProcessedWindow[aFreq] == 1);

    ////////////////////////////////////////////////////////////////

    int bFreq = 1024; 
    int bSampleRate = 4096; 
    std::vector<float> bSamples(bSampleRate, 0);

    for (int t = 0; t < bSampleRate; t++)
    {
        bSamples[t] =  sin(2*M_PI*bFreq*((double)t/bSampleRate));
    }

    Processor b(bSampleRate); 
    std::vector<float> bProcessedWindow = b.compute(bSamples);
    REQUIRE(bProcessedWindow[bFreq] == 1);

    /////////////////////////////////////////////////////////////////

    int cFreq = 512; 
    std::vector<float> cSamples(bSampleRate, 0);

    for (int t = 0; t < bSampleRate; t++)
    {
        cSamples[t] =  sin(2*M_PI*cFreq*((double)t/bSampleRate));
    }

    Processor c(bSampleRate); 
    std::vector<float> cProcessedWindow = c.compute(cSamples);
    REQUIRE(cProcessedWindow[cFreq] == 1);

    //////////////////////////////////////////////////////////////////

    int dFreq = 190;
    std::vector<float> dSamples(bSampleRate, 0);

    for (int t = 0; t < bSampleRate; t++)
    {
        dSamples[t] = bSamples[t] + cSamples[t] + sin(2*M_PI*dFreq*((double)t/bSampleRate));
    }

    Processor d(bSampleRate); 
    std::vector<float> dProcessedWindow = d.compute(dSamples);
    REQUIRE(dProcessedWindow[bFreq] == 1);
    REQUIRE(dProcessedWindow[cFreq] == 1);
    REQUIRE(dProcessedWindow[dFreq] == 1);
}