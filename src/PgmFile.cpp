#include "PgmFile.h"

///
///конструктор по подразбиране
///
PgmFile::PgmFile():pixels(NULL)
{
    this->setHeight(0);
    this->setWidth(0);
    this->setMaxColValue(0);
}

///
///конструктор за общо ползване
///
PgmFile::PgmFile(char* file){

    this->setFile(file);
    this->readFile();
}

///
///копиращ конструктор
///
PgmFile::PgmFile(PgmFile const &other){

    copyFrom(other);
}

///
///предефиниран оператор за присвояване
///
PgmFile& PgmFile::operator=(PgmFile const &other){

    if(this != &other){

        copyFrom(other);
    }

    return *this;
}

///
///деструктор
///
PgmFile::~PgmFile()
{
    destroy();
}

///
///записва съдържанието на файла
///
void PgmFile::readBinaryFile(ifstream &input){

    int sizeOfArray = this->getWidth() * this->getHeight();
    if(input){

        if(!isP2){

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
///продължава четенето на файла
///
void PgmFile::readFile(){

    ifstream input(fileName, ios::binary);
    if(input){

        startReading(input);
        this->pixels = new int[width * height];
        if(strcmp(getFormat(),"P5") ==0){

            this->isP2 = false;
            this->readBinaryFile(input);
        }
        else{

            this->isP2 = true;
            this->readBinaryFile(input);
        }
    }

    input.close();
}

///
///конвертиране на изображението до сиво
///
void PgmFile::convertToGrayscale(){
    std::cout<<"converting grayscale image to grayscale, really???\n";
}

///
///конвертиране на изображението до монохромно
///
void PgmFile::convertToMonochrome(){

    char monochrome[] ="_monochrome";
    this->setNewFileName(fileName,monochrome);
    if(isP2){

        this->asciiMonochrome();
    }
    else{

        this->binaryMonochrome();
    }
}

///
/// ковертиране на изображението до монохромно
///
int PgmFile::makeMonochrome(int index, int sizeOfImage){

    int digit;
    digit = this->pixels[index];
    if( digit < maxColValue / 2){

       digit = 0;
    }
    else{
       digit = maxColValue;
    }

    int color = pixels[index] - digit;
    if(index + 1 < sizeOfImage){

        pixels[index + 1] += color * (7.0 / 16);
    }
    if(index - 1 + width < sizeOfImage){

        pixels[index - 1 + width] += color * (3.0 / 16);
    }
    if(index + width < sizeOfImage){

        pixels[index + width] += color * (5.0 / 16);
    }
    if(index + 1  + width< sizeOfImage){

        pixels[index + 1 + width] += color * (1.0 / 16);
    }

    return digit;
}

///
///записване на изображението във текстов файл
///
void PgmFile::asciiMonochrome(){

    ofstream output(newFileName);

    int sizeOfArray = width * height;

    if(output){

        startRecording(output);
        for(int index = 0; index < sizeOfArray; ++index){

            int digit = makeMonochrome( index, sizeOfArray);
            output<<digit<<" ";
        }
    }

    output.close();
}

///
///записване на изображението във бинарен файл
///
void PgmFile::binaryMonochrome(){

    ofstream output(newFileName, ios::binary);

    int sizeOfArray = width * height;

    if(output){

        startRecording(output);
        char symbol;
        for(int index = 0; index < sizeOfArray; ++index){

            symbol = makeMonochrome(index, sizeOfArray);
            output.write((char*)&symbol, sizeof(unsigned char));
        }
    }

    output.close();
}

///
///хистограма..
///
void PgmFile::makeHistogram(HistogramColors choice){

}

///
///копираре на съдържанието на other
///
void PgmFile::copyFrom(PgmFile const &other){

    this->setWidth(other.width);
    this->setHeight(other.height);
    this->setMaxColValue(other.maxColValue);
    this->setFile(other.fileName);
}

///
///освобождаване на паметта
///
void PgmFile::destroy(){

    delete [] this->pixels;
    delete [] this->newFileName;
}
