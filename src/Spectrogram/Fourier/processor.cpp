#include "processor.h"

#include <iostream>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <string>

#define REAL 0
#define IMAG 1
#define POWER_TO_DB_MULT 10
#define EPSILON 1e-9

namespace Spectrogram::Fourier {

Processor::Processor(int wSize) : windowSize(wSize)
{
    validateWindowSize(wSize);
    setMembers(wSize);
}

Processor::Processor(const Processor &rhs)
{
    copyProcessor(rhs);
}

void Processor::validateWindowSize(const int& wSize) const
{
    if(wSize < 1)
    {
        throw std::invalid_argument("ERROR: windowSize = " + std::to_string(wSize) + ", must be larger than 1.");
    }
}

Processor::~Processor()
{
    cleanUp();
}

void Processor::cleanUp()
{
    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);
}

Processor& Processor::operator=(const Processor &rhs)
{
    if(this != &rhs)
    {
        cleanUp();
        copyProcessor(rhs);
    }
    return *this;
}

int Processor::calcComplexSize() const
{
    return  windowSize/2 + 1;
}

void Processor::copyProcessor(const Processor &rhs)
{
    setMembers(rhs.windowSize);
}

void Processor::setMembers(int newWindowSize)
{
    windowSize = newWindowSize;
    complexSize = calcComplexSize();
    in = fftw_alloc_real(windowSize);
    out = fftw_alloc_complex(complexSize);
    plan = fftw_plan_dft_r2c_1d(windowSize, in, out, FFTW_ESTIMATE);
}

void Processor::setSampleSize(int newSampleSize)
{
    validateWindowSize(newSampleSize);
    if (newSampleSize != windowSize)
    {
        cleanUp();
        setMembers(newSampleSize);
    }
}

int Processor::getSampleSize() const
{
    return windowSize;
}

int Processor::getOutputSize() const
{
    return complexSize;
}

Audio::Channel Processor::compute(const Audio::Channel& samples)
{
    in = applyHanningWindow(samples);

    out = executeFFT();

    Audio::Channel processedOutput = calcMagnitudeInDB();
    processedOutput = normalize(processedOutput);

    return processedOutput;
}

fftw_complex* Processor::executeFFT()
{
    fftw_execute(plan);

    return out;
}

Audio::Sample Processor::hann(const int &i, const int &n)
{
    return ( 1.0 - cos(2.0 * M_PI * i/ (n-1)) ) * 0.5;
}

double* Processor::applyHanningWindow(const Audio::Channel& samples)
{
    // The following for loop is a modification of the two for loops provided in URL
    //https://stackoverflow.com/questions/25061441/correct-way-to-implement-windowing/25061729#25061729?newreg=2a07fefa30ba41e1a286e025123513f8
    for (int i = 0; i < windowSize; i++)
    {
        in[i] = samples[i] * hann(i,windowSize);
    }
    return in;
}

// Magnitude equation adapted from stackoverflow user Hartmut Pfitzinger
// https://stackoverflow.com/questions/21283144/generating-correct-spectrogram-using-fftw-and-window-function
Audio::Channel Processor::calcMagnitudeInDB()
{
    Audio::Channel magnitudeDB(complexSize, 0);
    // Since only have half the complex values multiply by 2, (do not have conjugates)
    // And divide by sample size to get ratio
    float scale = 2.0 / windowSize;
    for (int i = 0; i < complexSize; i++)
    {
        // Power spectral density is |real|^2 + |imag|^2
        magnitudeDB[i] = pow(out[i][REAL] * scale, 2) + pow(out[i][IMAG] * scale, 2);

        // Convert from power to decibel for color intensity display
        magnitudeDB[i] = convertToDb(magnitudeDB[i]);
    }

    return magnitudeDB;
}

Audio::Sample Processor::convertToDb(const Audio::Sample &val)
{
    // Epsilon is to make sure we don't do log(0)
    Audio::Sample dBVal = POWER_TO_DB_MULT * std::log10(val + EPSILON);

    return dBVal;
}

// TODO: if this is slowing down the processing too much, there is
// a rougher way to normalize without having to find the min and max
Audio::Channel& Processor::normalize(Audio::Channel& v)
{
    Audio::Sample max = *std::max_element(v.begin(), v.end());
    Audio::Sample min = *std::min_element(v.begin(), v.end());

    if (max == min)
    {
        throw std::domain_error("ERROR: " + std::to_string(max) + ", all the values are the same in this Channel.");
    }

    // Normalization adapted from user Alex I from stackoverflow
    // https://stackoverflow.com/questions/21283144/generating-correct-spectrogram-using-fftw-and-window-function
    for(auto it = v.begin(); it != v.end(); ++it)
    {
        *it = (*it - min) / (max - min);
    }
    return v;
}

}