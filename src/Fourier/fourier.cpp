#include "fourier.h"

#include <fftw3.h>
#include <iostream>
#include <cmath>

/**
 * Order of operations:
 * 
 * applyHanningWindow
 * executeFFT
 * normalize
 * 
**/

#define REAL 0
#define IMAG 1

namespace Fourier {

    double* copySamples(double* in, double* samples, int sampleSize)
    {
        for (int i = 0; i < sampleSize; i++)
        {
            in[i] = samples[i];
        }
        return in;
    }

    // The following two functions hann and applyingHanningWindow
    // are a modification of the two for loops on stackoverflow by user r3mainer
    // https://stackoverflow.com/questions/25061441/correct-way-to-implement-windowing/25061729#25061729?newreg=2a07fefa30ba41e1a286e025123513f8
    double hann(const int &i, const int &n)
    {
        return ( 1.0 - cos(2.0 * M_PI * i/ (n-1)) ) * 0.5;;
    }

    double* applyHanningWindow(double* in, int windowSize)
    {
        for (int i = 0; i < windowSize; i++) 
        {
            in[i] *= hann(i,windowSize);
        }
        return in;
    }

    void normalize()
    {
        // TODO: Normalize the output
    }

    double complexOutSize(int n) 
    {
        return n/2 + 1;
    }

    void process(double samples[], const int &inSampleSize)
    {
        // TODO: fix this
        if(inSampleSize < 1)
            throw 1;

        double *in = fftw_alloc_real(inSampleSize);

        int outSampleSize = complexOutSize(inSampleSize);
        // This is equivalent to a 2D array: 
        // double out[sampleSize][2]<-- 0 = real part and 1 = imaginary part
        fftw_complex *out = fftw_alloc_complex(outSampleSize);
        // This makes the "plan" that will perform DFT on the 1D real data in "in"
        // And put the tranformed complex data in "out" 
        fftw_plan plan = fftw_plan_dft_r2c_1d(inSampleSize, in, out, FFTW_ESTIMATE);

        in = copySamples(in, samples, inSampleSize);

        // TODO: for testing purposes, remove later
        for (int i=0; i< inSampleSize; i++)
            std::cout << in[i] << ", ";
        std::cout << std::endl;

        in = applyHanningWindow(in, inSampleSize);
        // This populates "out" with the complex values
        fftw_execute(plan);
        
        normalize();

        //TODO: for testing purposes, remove later
        for (int i=0; i< inSampleSize; i++)
            std::cout << in[i] << ", ";
        std::cout << std::endl;
        std::cout << "FFT = " << std::endl;
        for (int i=0; i< outSampleSize; i++)
            if(out[i][IMAG] < 0)
                std::cout << out[i][REAL] << " - " << abs(out[i][IMAG]) << "i" << std::endl;
            else
                std::cout << out[i][REAL] << " + " << abs(out[i][IMAG]) << "i" << std::endl;

        fftw_destroy_plan(plan);
        fftw_free(in); 
        fftw_free(out);
    }

}