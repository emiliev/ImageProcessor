#ifndef PPMFILE_H
#define PPMFILE_H

#include "Image.h"

using namespace std;
class PpmFile: public Image
{
    public:
        PpmFile();
        PpmFile(File &);
        PpmFile(PpmFile const &);
        PpmFile& operator=(PpmFile const &);
        ~PpmFile();

        void convertToGrayscale();
        void convertToMonochrome();
        void readBinaryFile(ifstream &);
        void makeHistogram(HistogramColors);

    protected:
    private:
        bool isP3;

        File file;
        Pixel* pixels;

        void copyFrom(PpmFile const &);
        void destroy();

        void readFile(File &);
        void binaryGrayscale();
        void binaryMonochrome();
        void asciiGrayscale();
        void asciiMonochrome();
        void histogram(char*, HistogramColors);
};

#endif // PPMFILE_H
