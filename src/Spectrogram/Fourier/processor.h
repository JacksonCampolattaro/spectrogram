#ifndef SPECTROGRAM_PROCESSOR_H
#define SPECTROGRAM_PROCESSOR_H

#include <vector>
#include <fftw3.h>
#include <Spectrogram/Audio/Buffer.h>

/**
 * @brief Contains all functionality related to performing fourier calculations
 */
namespace Spectrogram::Fourier {

    /**
     * @brief Fast fourier transform utility built on top of the library FFTW3
     *
     * @todo
     */
    class Processor {
    public:

        /**
         * @brief Constructor for a new Fourier processor with a fixed window size
         * @param wSize Hanning window size, set permanently
         */
        explicit Processor(int wSize = 2048);

        /**
         * @brief Copy constructor which duplicates the FFTW3 setup of the other Processor
         * @param rhs
         */
        Processor(const Processor &rhs);

        /**
         * @brief Destructor which safely frees all resources used by FFTW3
         */
        ~Processor();

        /**
         * @brief Copy constructor which re-initializes FFTW3
         * @param rhs
         * @return
         */
        Processor &operator=(const Processor &rhs);

        /**
         * @brief Compute the spectrogram output vector from input data
         * @param samples Vector of floats from audio stream, size of windowSize
         * @return Vector of floats half the size of the input in decibels, with normalized values between 0 and 1
         */
        Audio::Channel compute(const Audio::Channel &samples);

        /**
         * @brief Getter for the Hanning window size
         * @return the windowSize, which is the input array length
         */
        int getSampleSize() const;

        /**
         * @brief Getter for the size of the output array
         * @return the output array size that is produced after processing the input
         */
        int getOutputSize() const;

        /**
         * @brief Change the window size
         *
         * @todo Is this used?
         *
         * @param newSampleSize
         */
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
