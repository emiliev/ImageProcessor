#include "PbmFile.h"
///
///Конструктор по подразбиране
///
PbmFile::PbmFile():pixels(NULL)
{
    this->setHeight(0);
    this->setWidth(0);
    this->pixels = new int[height * width];
}

///
///Конструктор за общо ползване
///
PbmFile::PbmFile(char* file):pixels(NULL)
{
    this->setFile(file);
    this->readFile();
}

///
///Копиращ конструктор
///
PbmFile::PbmFile(PbmFile const &other):pixels(NULL)
{
    copyFrom(other);
}

///
///Оператор за присвояване
///
PbmFile& PbmFile::operator=(PbmFile const &other){

    if(this != &other){

        copyFrom(other);
    }

    return *this;
}

///
///продължава записването на файла
///
void PbmFile::readFile(){

    ifstream input(fileName, ios::binary);
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

///
///записване на сдържанието на файла
///
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

///
///хистограма
///
void PbmFile::makeHistogram(HistogramColors choice){

}
///
///конвертиране на изображението до сиво
///
void PbmFile::convertToGrayscale(){
    std::cout<<"monochrome -> grayscale ? \n";
}

///
///конвертиране на изображението до черно-бяло
///
void PbmFile::convertToMonochrome(){

    std::cout<<"monochrome -> monochrome ? \n";
}

///
///деструктор
///
PbmFile::~PbmFile()
{
    destroy();
}

///
///освобождаване на памеетта
///
void PbmFile::destroy(){

    delete [] this->pixels;
}

///
///копира съдържанието на other
///
void PbmFile::copyFrom(PbmFile const &other){

    this->setWidth(other.width);
    this->setHeight(other.height);
}
