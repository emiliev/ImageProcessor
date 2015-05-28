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
       // PpmFile& operator=(PpmFile const &);
        ~PpmFile();

        void setHeight(int);
        void setWidth(int);
        void setMaxColValue(int);
        int getHeight();
        int getWidth();

        void convertToGrayscale();
        void convertToASCIIGrayScale();
        void readASCIIFile(ifstream &);
        void readBinaryFile(File &o);

    protected:
    private:
        int maxColValue;
        int height;
        int width;
        Pixel* pixels;
        char* newFileName;
        char* getNewFileName(File &);
        void copyFrom(PpmFile const &);
        void destroy();

        void readFile(File &);

};

#endif // PPMFILE_H
