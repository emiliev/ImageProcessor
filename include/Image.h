#ifndef IMAGE_H
#define IMAGE_H

#include "Pixel.h"
#include "File.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

class Image
{
    public:
        Image();
        Image(File &);
        Image(const Image& other);
        Image& operator=(Image const &);
        ~Image();

        virtual void readASCIIFile(ifstream &) = 0;
        virtual void readBinaryFile(File &) = 0;
        virtual void convertToGrayscale() = 0;

    protected:

    private:


};

#endif // IMAGE_H
