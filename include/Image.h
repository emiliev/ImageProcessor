#ifndef IMAGE_H
#define IMAGE_H

#include "Pixel.h"
#include "File.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

 enum HistogramColors{RED ,GREEN,BLUE};

class Image
{
    public:
        Image();
        Image(File &);
        Image(const Image& other);
        Image& operator=(Image const &);
        ~Image();

        virtual void convertToGrayscale() = 0;
        virtual void convertToMonochrome() = 0;
        virtual void readBinaryFile(ifstream &) = 0;
        virtual void makeHistogram(HistogramColors ) =0;
        void startReading(ifstream &);
        void startRecording(ofstream &);
        char* getFormat();

        int getHeight();
        int getWidth();
        int getMaxColValue();

    protected:
        int maxColValue;
        int height;
        int width;
        char* newFileName;
        void setHeight(int);
        void setWidth(int);
        void setMaxColValue(int);


        void setNewFileName(File &, char *);

        private:

        char format[2];
        bool compareFormat(char* format);
};

#endif // IMAGE_H
