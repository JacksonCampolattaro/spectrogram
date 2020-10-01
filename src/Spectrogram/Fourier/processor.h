#ifndef SPECTROGRAM_FOURIER_PROCESSOR_H
#define SPECTROGRAM_FOURIER_PROCESSOR_H

/**
 * Order of operations:
 * 
 * applyHanningWindow
 * executeFFT
 * normalize
 * 
**/
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
        std::vector<float> compute(float[]);

    private:
        float calcComplexSize() const;
        void executeFFT();
        void applyHanningWindow(float samples[]);
        std::vector<float> calcMagnitudeInDB();
        float convertToDb(const float &val);
        std::vector<float>& normalize(std::vector<float>& v);

        // Calculate Hann
        float hann(const int&, const int&);
        void copyProcessor(const Processor &rhs);
        // Destroy the plan and free the arrays
        void cleanUp();
        void printIn();

        //int strideSize;
        //int sampleSize; 
        int complexSize;
        int windowSize; // Provided by audio stream, the amount of floats inside the sample
        double *in; // size is dependent on the sampling size
        fftw_complex* out;
        fftw_plan plan;
};

}

#endif //SPECTROGRAM_FOURIER_PROCESSOR_H
