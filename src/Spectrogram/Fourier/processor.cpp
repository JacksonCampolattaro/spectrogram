#include "processor.h"

#include <iostream>
#include <cmath>
#include <algorithm>


#define REAL 0
#define IMAG 1
#define POWER_TO_DB_MULT 10
#define EPSILON 1e-9
#define MAX_DB 96.0

namespace Fourier {

Processor::Processor(int wSize=2048) : windowSize(wSize)
{
    // TODO: fix this
    if(wSize < 1)
        throw 1;
    complexSize = calcComplexSize();
    in = fftw_alloc_real(windowSize);
    out = fftw_alloc_complex(complexSize);
    plan = fftw_plan_dft_r2c_1d(windowSize, in, out, FFTW_ESTIMATE);
}

Processor::Processor() : Processor(2048)
{
    // TODO: figure out what data struct to use for input
}

Processor::Processor(const Processor &rhs) 
{
    copyProcessor(rhs);
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

// assignment operator
Processor& Processor::operator=(const Processor &rhs)
{
    if(this != &rhs)
    {
        this->cleanUp();
        copyProcessor(rhs);
    }
    return *this;
}

std::vector<float> Processor::compute(float samples[])
{
    applyHanningWindow(samples);

    std::cout << "\nHann: ";
    printIn();
    std::cout << "\n";

    executeFFT();
    std::vector<float> processedOutput = calcMagnitudeInDB();
    processedOutput = normalize(processedOutput);

    return processedOutput;
}

void Processor::executeFFT() 
{
    fftw_execute(plan);
}

float Processor::hann(const int &i, const int &n)
{
    return ( 1.0 - cos(2.0 * M_PI * i/ (n-1)) ) * 0.5;
}

void Processor::applyHanningWindow(float samples[])
{
    // The following for loop is a modification of the two for loops provided in URL
    //https://stackoverflow.com/questions/25061441/correct-way-to-implement-windowing/25061729#25061729?newreg=2a07fefa30ba41e1a286e025123513f8
    for (int i = 0; i < windowSize; i++) 
    {
        in[i] = samples[i] * hann(i,windowSize);
    }
}

// TODO: might be able to not pass in inWindowSize by just doing (outWindowSize-1) * 2
// Power and decibel equations adapted from stackoverflow user Hartmut Pfitzinger
// https://stackoverflow.com/questions/21283144/generating-correct-spectrogram-using-fftw-and-window-function
std::vector<float> Processor::calcMagnitudeInDB()
{
    std::vector<float> magnitudeDB(complexSize, 0);
    // Since only have half the complex values multiply by 2, (do not have conjugates)
    // And divide by sample size to get ratio
    float scale = 2.0 / windowSize;
    std::cout << "\nout:\n";
    for (int i = 0; i < complexSize; i++)
    {
        std::cout << out[i][REAL] << ", ";
        // Power spectral density is |real|^2 + |imagin|^2
        magnitudeDB[i] = pow(out[i][REAL] * scale, 2) + pow(out[i][IMAG] * scale, 2);
        std::cout << magnitudeDB[i] << ", ";
        // Convert from power to decibel for color intensity display 
        // Epsilon is to make sure we don't do log(0)
        magnitudeDB[i] = convertToDb(magnitudeDB[i]);
    }

    return magnitudeDB;
}

float Processor::convertToDb(const float &val)
{
    float dBVal = POWER_TO_DB_MULT * std::log10(val + EPSILON); 

    return dBVal;
}

std::vector<float>& Processor::normalize(std::vector<float>& v)
{
    float max = *std::max_element(v.begin(), v.end());
    float min = *std::min_element(v.begin(), v.end());
    // //TODO: fix this
    // if (max <= 0)
    //     throw 1;
    // std::cout << "Max: " << max;
    // for(auto it = v.begin(); it != v.end(); ++it)
    // {
    //     // TODO: Think this needs to happen for spectrogram display
    //     // cut off negative values
    //     if (*it < 0)
    //         *it = 0;
    //     else
    //         *it = *it/max;
    // }
    // Credit: Alex I from stackoverflow
    // https://stackoverflow.com/questions/21283144/generating-correct-spectrogram-using-fftw-and-window-function
    for(auto it = v.begin(); it != v.end(); ++it)
    {
        *it = (*it - min) / (max - min);
    }
    return v;
}

float Processor::calcComplexSize() const
{
    return  windowSize/2 + 1;
}

void Processor::copyProcessor(const Processor &rhs)
{
    windowSize = rhs.windowSize;
    in = fftw_alloc_real(rhs.windowSize);
    out = fftw_alloc_complex(complexSize);
    plan = fftw_plan_dft_r2c_1d(windowSize, in, out, FFTW_ESTIMATE);
}

void Processor::printIn()
{
    for (int i=0; i< windowSize; i++)
        std::cout << in[i] << ", ";
}

}