#include "PgmFile.h"

PgmFile::PgmFile():pixels(NULL)
{
    this->setHeight(0);
    this->setWidth(0);
    this->setMaxColValue(0);
}

PgmFile::PgmFile(File &file){

    this->readFile(file);
    this->getNewFileName(file);
}

PgmFile::PgmFile(PgmFile const &other){

    copyFrom(other);
}

PgmFile& PgmFile::operator=(PgmFile const &other){

    if(this != &other){

        copyFrom(other);
    }

    return *this;
}

PgmFile::~PgmFile()
{
    destroy();
}

///populate array from .pgn file
void PgmFile::readBinaryFile(ifstream &input){

    int sizeOfArray = this->width * this->height;
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


///starts reading file
void PgmFile::readFile(File  &file){

    char buffer[3];
    ifstream input(file.getFileName(), ios::binary);
    std::cout<<file.getFileName()<<std::endl;
    if(input){

        input.read(buffer,sizeof(char) * 3);
        std::cout<<buffer<<std::endl;
        int w,h,m;
        input>>w>>h>>m;
        this->setWidth(w);
        this->setHeight(h);
        this->setMaxColValue(m);
        this->pixels = new int[width * height];

        if(strcmp(buffer,"P5\n") ==0){

            std::cout<<"faila e p5!\n";
            this->isP2 = false;
            this->readBinaryFile(input);
        }
        else{

            std::cout<<"faila e p2!\n";
            this->isP2 = true;
            this->readBinaryFile(input);
        }
    }

    input.close();
}

char* PgmFile::getNewFileName(File  &file){

    char grayscale[] = "_monochrome";
    int sizeOfGrayscale = strlen(grayscale);
    int sizeOfFile = strlen(file.getFileName());
    int sizeOfNewFile = sizeOfFile + sizeOfGrayscale + 1;
    newFileName = new char[sizeOfNewFile];
    strcpy(newFileName,file.getFileName());

    for(int index = sizeOfFile - 4; index <= sizeOfFile; ++index){

        newFileName[index + sizeOfGrayscale] = newFileName[index];
    }

    for(int index = 0 ;index <sizeOfGrayscale; ++index){
        newFileName[sizeOfFile - 4 + index] = grayscale[index];
    }

    return newFileName;
}

void PgmFile::convertToGrayscale(){
    std::cout<<"converting grayscale image to grayscale, really???\n";
}

void PgmFile::convertToMonochrome(){

    if(isP2){

        this->asciiMonochrome();
    }
    else{

        this->binaryMonochrome();
    }
}

void PgmFile::asciiMonochrome(){

    ofstream output(newFileName);
    int sizeOfArray = width * height;

    if(output){
        char buffer[] = "P2\n";
        output.write(buffer,sizeof(char) * 3);
        output<<this->getWidth()<<" "<<this->getHeight()<<endl<<this->maxColValue<<endl;

        for(int index = 0; index < sizeOfArray; ++index){

            int digit = pixels[index];
            ///i tyk!!
           /* if(digit > maxColValue / 2){

                digit = 0;
            }
            else{

                digit = maxColValue;
            }*/

            output<<digit<<" ";
        }
    }

    output.close();
}

void PgmFile::binaryMonochrome(){

    ofstream output(newFileName, ios::binary);
    int sizeOfArray = width * height;


    if(output){
        char buffer[] = "P5\n";
        output.write(buffer,sizeof(char) * 3);
        output<<this->getWidth()<<" "<<this->getHeight()<<endl<<this->maxColValue<<endl;

        char symbol;
        for(int index = 0; index < sizeOfArray; ++index){

            symbol = pixels[index];

            ///predstoi obrabotka !!!
          /*  if(symbol > maxColValue / 2){

                symbol = 10;
            }
            else{

                symbol = maxColValue;
            }
            */
            output.write((char*)&symbol, sizeof(unsigned char));
        }
    }

    output.close();
}

void PgmFile::makeHistogram(HistogramColors choice){

}

void PgmFile::setHeight(int newSize){

    this->height = newSize;
}

int PgmFile::getHeight(){

    return this->height;
}

void PgmFile::setWidth(int newSize){

    this->width = newSize;
}

int PgmFile::getWidth(){

    return this->width;
}

void PgmFile::setMaxColValue(int newSize){

    this->maxColValue = newSize;
}

int PgmFile::getMaxColValue(){

    return this->maxColValue;
}

void PgmFile::copyFrom(PgmFile const &other){

    this->setWidth(other.width);
    this->setHeight(other.height);
    this->setMaxColValue(other.maxColValue);
}

void PgmFile::destroy(){

    delete [] this->pixels;
    delete [] this->newFileName;
}
