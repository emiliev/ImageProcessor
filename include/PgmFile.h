#ifndef PGMFILE_H
#define PGMFILE_H

#include "Image.h"

class PgmFile:public Image
{
    public:
        PgmFile();
        PgmFile(char*);
        PgmFile(PgmFile const &);
        PgmFile& operator=(PgmFile const &);
        ~PgmFile();

        void convertToGrayscale();
        void convertToMonochrome();
        int makeMonochrome(int, int);
        void readBinaryFile(ifstream &);
        void makeHistogram(HistogramColors);

    protected:
    private:

        char* fileName;
        bool isP2;
        int* pixels;

        void copyFrom(PgmFile const &);
        void destroy();
        void readFile();
        void asciiMonochrome();
        void binaryMonochrome();
};

#endif // PGMFILE_H
