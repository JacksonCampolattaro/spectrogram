#ifndef SPECTROGRAM_FOURIER_PROCESSOR_H
#define SPECTROGRAM_FOURIER_PROCESSOR_H

#include <vector>
#include <fftw3.h>

namespace Fourier {

class Processor {
    public:
        // Default
        Processor();
        // Parameterized
        Processor(int wSize);
        // Copy Constructor
        Processor(const Processor &rhs);
        // Destructor
        ~Processor();
        // Assignment operator
        Processor& operator=(const Processor &rhs);
        // Compute the spectrogram output vector from input data
        // Input: Vector of floats from audio stream, size of windowSize
        // Output: Vector of floats half the size of the input in decibels that 
        //         have been normalized to be between 0 and 1
        std::vector<float> compute(const std::vector<float>& samples);
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
        void executeFFT();
        // Applies hanning window to input data and copies the windowed data to 'in' array
        double* applyHanningWindow(const std::vector<float>& samples);
        // Gets the magnitude of the complex values and converts to decibels
        std::vector<float> calcMagnitudeInDB();
        // Converts magnitude to decibels
        float convertToDb(const float &val);
        // Normalizes the data to be between 0 and 1
        std::vector<float>& normalize(std::vector<float>& v);

        // Calculate Hann
        float hann(const int&, const int&);
        // Copy another processor's members to this object
        void copyProcessor(const Processor &rhs);
        // Sets this objects members
        void setMembers(int newWindowSize);
        // Destroy the plan and free the arrays
        void cleanUp();

        int complexSize; // Output array size
        int windowSize; // Provided by audio stream, the amount of floats inside the sample
        double *in; // size is dependent on the window size
        fftw_complex* out; // complex output array
        fftw_plan plan; // Plan to perform the FFT on the real data to complex
};

}

#endif //SPECTROGRAM_FOURIER_PROCESSOR_H
