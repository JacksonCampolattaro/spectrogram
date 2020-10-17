#ifndef SPECTROGRAM_PROCESSOR_H
#define SPECTROGRAM_PROCESSOR_H

#include <vector>
#include <fftw3.h>
#include <Spectrogram/Audio/Buffer.h>

namespace Spectrogram::Fourier {

    class Processor {
    public:
        // Parameterized
        explicit Processor(int wSize = 2048);

        // Copy Constructor
        Processor(const Processor &rhs);

        // Destructor
        ~Processor();

        // Assignment operator
        Processor &operator=(const Processor &rhs);

        // Compute the spectrogram output vector from input data
        // Input: Vector of floats from audio stream, size of windowSize
        // Output: Vector of floats half the size of the input in decibels that 
        //         have been normalized to be between 0 and 1
        Audio::Channel compute(const Audio::Channel &samples);

        // Returns the windowSize, which is the input array length
        int getSampleSize() const;

        // Returns the output array size that is produced after processing the input
        int getOutputSize() const;

        // Sets the windowSize to something else
        void setSampleSize(int newSampleSize);

    private:
        // Returns the output array size
        int calcComplexSize() const;

        // Executes the FFT using FFTW3 library
        fftw_complex *executeFFT();

        // Applies hanning window to input data and copies the windowed data to 'in' array
        double *applyHanningWindow(const Audio::Channel &samples);

        // Gets the magnitude of the complex values and converts to decibels
        Audio::Channel calcMagnitudeInDB();

        // Converts magnitude to decibels
        Audio::Sample convertToDb(const Audio::Sample &val);

        // Normalizes the data to be between 0 and 1
        Audio::Channel &normalize(Audio::Channel &v);

        // Calculate Hann
        float hann(const int &, const int &);

        // Copy another processor's members to this object
        void copyProcessor(const Processor &rhs);

        // returns true if window size is greater then 1
        // throws a runtime error if window size is less then 1
        void validateWindowSize(const int &wSize) const;

        // Sets this objects members
        void setMembers(int newWindowSize);

        // Destroy the plan and free the arrays
        void cleanUp();

        int complexSize; // Output array size
        int windowSize; // Provided by audio stream, the amount of floats inside the sample
        double *in; // size is dependent on the window size
        fftw_complex *out; // complex output array
        fftw_plan plan; // Plan to perform the FFT on the real data to complex
    };

}

#endif //SPECTROGRAM_PROCESSOR_H
