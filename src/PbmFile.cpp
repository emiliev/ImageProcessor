#include "PbmFile.h"

PbmFile::PbmFile():pixels(NULL)
{
    this->setHeight(0);
    this->setWidth(0);
    this->pixels = new int[height * width];
}

PbmFile::PbmFile(File &other):pixels(NULL)
{

    this->readFile(other);
}

PbmFile::PbmFile(PbmFile const &other):pixels(NULL)
{
    copyFrom(other);
}

PbmFile& PbmFile::operator=(PbmFile const &other){

    if(this != &other){

        copyFrom(other);
    }

    return *this;
}

void PbmFile::readFile(File &file){

    ifstream input(file.getFileName(), ios::binary);
    if(input){

        startReading(input);
        this->pixels = new int[width * height];
        if(strcmp(getFormat(),"P4\n") ==0){

            this->isP1 = false;
            this->readBinaryFile(input);
        }
        else{

            this->isP1 = true;
            this->readBinaryFile(input);
        }
    }

    input.close();
}
void PbmFile::readBinaryFile(ifstream &input){

    int sizeOfArray = this->width * this->height;
    if(input){

        if(!isP1){

            unsigned char digit;
            for(int index = 0; index < sizeOfArray; ++index){

                input.read((char*)&digit,sizeof(unsigned char));
                this->pixels[index] = digit;
            }
        }
        else{

            int digit;
            for(int index = 0; index < sizeOfArray; ++index){

                input>>digit;
                this->pixels[index] = digit;
            }
        }
   }

   input.close();
}

void PbmFile::makeHistogram(HistogramColors choice){

}

void PbmFile::convertToGrayscale(){
    std::cout<<"monochrome -> grayscale ? \n";
}

void PbmFile::convertToMonochrome(){

    std::cout<<"monochrome -> monochrome ? \n";
}

PbmFile::~PbmFile()
{
    destroy();
}

void PbmFile::destroy(){

    delete [] this->pixels;
}

void PbmFile::copyFrom(PbmFile const &other){

    this->setWidth(other.width);
    this->setHeight(other.height);
}
