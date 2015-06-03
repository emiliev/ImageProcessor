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

        void convertToGrayscale();
        void convertToMonochrome();
        void readBinaryFile(ifstream &);
        void makeHistogram(HistogramColors);

    protected:
    private:

        File someFile;
        bool isP2;
        int* pixels;

        void copyFrom(PgmFile const &);
        void destroy();
        void readFile(File  &);
        void asciiMonochrome();
        void binaryMonochrome();
};

#endif // PGMFILE_H
