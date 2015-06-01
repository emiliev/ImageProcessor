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

        void setHeight(int);
        void setWidth(int);
        void setMaxColValue(int);
        int getHeight();
        int getWidth();

        void convertToGrayscale();
        void convertToMonochrome();
        void readBinaryFile(ifstream &);
        void makeHistogram(HistogramColors);

    protected:
    private:
        bool isP3;

        File file;
        int maxColValue;
        int height;
        int width;
        Pixel* pixels;
        char* newFileName;
        void setNewFileName(File &, char *);
        void copyFrom(PpmFile const &);
        void destroy();

        void readFile(File &);
        void binaryGrayscale();
        void binaryMonochrome();
        void asciiGrayscale();
        void asciiMonochrome();
        void histogram();
};

#endif // PPMFILE_H
