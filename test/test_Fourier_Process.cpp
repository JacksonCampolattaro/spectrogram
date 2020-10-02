#include <catch2/catch.hpp>

#include <Spectrogram/Fourier/processor.h>
#include <iostream>

TEST_CASE("Test constructors", "[Fourier::Processor]") {

    Fourier::Processor a(5); 
    REQUIRE(a.getSampleSize() == 5);
    REQUIRE(a.getOutputSize() == 3);
    

    Fourier::Processor b;
    a = b;
    REQUIRE(b.getSampleSize() == 2048);
    REQUIRE(b.getOutputSize() == 1025);
    REQUIRE(a.getSampleSize() == 2048);
    REQUIRE(a.getOutputSize() == 1025);

    Fourier::Processor c(a); 
    REQUIRE(c.getSampleSize() == 2048);
    REQUIRE(c.getOutputSize() == 1025);

    REQUIRE_THROWS_AS(Fourier::Processor(0), std::invalid_argument);

}

TEST_CASE("Test setters", "[Fourier::Processor]") {
    Fourier::Processor a(1024);
    REQUIRE(a.getSampleSize() == 1024);
    REQUIRE(a.getOutputSize() == 513);

    a.setSampleSize(16384);
    REQUIRE(a.getSampleSize() == 16384);
    REQUIRE(a.getOutputSize() == 8193);

}

TEST_CASE("Test math", "[Fourier::Processor]") {
    
    int aFreq = 3; // Hz
    int aSampleRate = 100; 
    float aSamples[aSampleRate];

    for (int t = 0; t < aSampleRate; t++)
    {
        aSamples[t] =  sin(2*M_PI*aFreq*((double)t/aSampleRate));
    }

    Fourier::Processor a(aSampleRate); 
    std::vector<float> aProcessedWindow = a.compute(aSamples);
    std::cout << "freq bin 3 should be 1 since the freq = 3:\n";
    std::cout << "output:\n";
    for(float db : aProcessedWindow)
        std::cout << db << ", ";
    std::cout << std::endl;
    REQUIRE(aProcessedWindow[aFreq] == Approx(1));

    ////////////////////////////////////////////////////////////////

    int bFreq = 1024; 
    int bSampleRate = 4096; 
    float bSamples[bSampleRate];

    for (int t = 0; t < bSampleRate; t++)
    {
        bSamples[t] =  sin(2*M_PI*bFreq*((double)t/bSampleRate));
    }

    Fourier::Processor b(bSampleRate); 
    std::vector<float> bProcessedWindow = b.compute(bSamples);
    REQUIRE(bProcessedWindow[bFreq] == Approx(1));

    /////////////////////////////////////////////////////////////////

    int cFreq = 512; 
    float cSamples[bSampleRate];

    for (int t = 0; t < bSampleRate; t++)
    {
        cSamples[t] =  sin(2*M_PI*cFreq*((double)t/bSampleRate));
    }

    Fourier::Processor c(bSampleRate); 
    std::vector<float> cProcessedWindow = c.compute(cSamples);
    REQUIRE(cProcessedWindow[cFreq] == Approx(1));

    //////////////////////////////////////////////////////////////////

    int dFreq = 190;
    float dSamples[bSampleRate];

    for (int t = 0; t < bSampleRate; t++)
    {
        dSamples[t] = bSamples[t] + cSamples[t] + sin(2*M_PI*dFreq*((double)t/bSampleRate));
    }

    Fourier::Processor d(bSampleRate); 
    std::vector<float> dProcessedWindow = d.compute(dSamples);
    REQUIRE(dProcessedWindow[bFreq] == Approx(1));
    REQUIRE(dProcessedWindow[cFreq] == Approx(1));
    REQUIRE(dProcessedWindow[dFreq] == Approx(1));
}