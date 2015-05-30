#ifndef PBMFILE_H
#define PBMFILE_H

#include "Image.h"

class PbmFile: public Image
{
    public:
        PbmFile();
        PbmFile(File& file);
        PbmFile(PbmFile const &);
        PbmFile& operator=(PbmFile const &);

        void setWidth(int);
        void setHeight(int);
        int getWidth();
        int getHeight();

        void convertToGrayscale();
        void convertToMonochrome();
        void readBinaryFile(ifstream &);
        void makeHistogram(HistogramColors);

        ~PbmFile();
    protected:
    private:
        int width,height;
        int* pixels;
        bool isP1;

        void readFile(File &);
        void copyFrom(PbmFile const &);
        void destroy();
};

#endif // PBMFILE_H
