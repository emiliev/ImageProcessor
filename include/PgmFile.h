#ifndef PGMFILE_H
#define PGMFILE_H

#include "Image.h"

class PgmFile:public Image
{
    public:
        PgmFile();
        PgmFile(File &);
        PgmFile(PgmFile const &);
        PgmFile& operator=(PgmFile const &);
        ~PgmFile();

        void setHeight(int);
        void setWidth(int);
        void setMaxColValue(int);
        int getHeight();
        int getWidth();
        int getMaxColValue();

        void convertToGrayscale();
        void convertToMonochrome();
        void readBinaryFile(ifstream &);
        void makeHistogram(HistogramColors);

    protected:
    private:

        bool isP2;
        int width;
        int height;
        int maxColValue;
        int* pixels;
        void copyFrom(PgmFile const &);
        void destroy();
        char* newFileName;
        char* getNewFileName(File &);

        void readFile(File  &);
        void asciiMonochrome();
        void binaryMonochrome();
};

#endif // PGMFILE_H
