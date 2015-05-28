#include "PpmFile.h"



PpmFile::PpmFile():pixels(NULL)
{
    this->pixels = new Pixel[0];
    this->setHeight(0);
    this->setWidth(0);
}

PpmFile::PpmFile(File &otherFile):pixels(NULL){
   // this->readFile(otherFile);
    this->getNewFileName(otherFile);
    this->readBinaryFile(otherFile);
    this->convertToGrayscale();

}

PpmFile::PpmFile(PpmFile const &other):pixels(NULL){

    copyFrom(other);
}

/*PpmFile& PpmFile::operator=(PpmFile const &other):pixels(NULL){

    if(this != &other){

        copyFrom(other);
    }

    return *this;
}
*/
PpmFile::~PpmFile()
{
    destroy();
}

int PpmFile::getHeight(){

    return this->height;
}

int PpmFile::getWidth(){

    return this->width;
}
void PpmFile::setHeight(int h){

    this->height = h;
}

void PpmFile::setWidth(int w){

    this->width = w;
}

void PpmFile::setMaxColValue(int m){

    this->maxColValue = m;
}

void PpmFile::copyFrom(PpmFile const &other){

    this->setWidth(other.width);
    this->setHeight(other.height);
}
/*
void PpmFile::readFile(File &file){

    char buffer[3];
    ifstream input(file.getFileName(), ios::binary);

    if(input){

        input>>buffer;
        int w,h,m;
        input>>w>>h>>m;
        this->setWidth(w);
        this->setHeight(h);
        this->setMaxColValue(m);
        this->pixels = new Pixel[width * height];
        if(strcmp(buffer,"P6") ==0){
            std::cout<<"faila e p6!\n";
            this->readBinaryFile(input);
        }
        else{

            std::cout<<"faila e p3!\n";
            this->readASCIIFile(input);
        }
    }

    input.close();
}*/

char* PpmFile::getNewFileName(File &fileName){

    char grayscale[] = "_grayscale";
    int sizeOfGrayscale = strlen(grayscale);
    int sizeOfFile = strlen(fileName.getFileName());
    int sizeOfNewFile = sizeOfFile + sizeOfGrayscale + 1;
    newFileName = new char[sizeOfNewFile];
    strcpy(newFileName,fileName.getFileName());

    for(int index = sizeOfFile - 4; index < sizeOfFile; ++index){

        newFileName[index + sizeOfGrayscale] = newFileName[index];
    }

    for(int index = 0 ;index <sizeOfGrayscale; ++index){
        newFileName[sizeOfFile - 4 + index] = grayscale[index];
    }
    std::cout<<newFileName<<std::endl;

    return newFileName;
}

void PpmFile::readASCIIFile(ifstream &input){

    if(input){
        int r,g,b;
        int pixelArraySize = this->width * this->height;
        for(int index = 0; index <pixelArraySize; ++index){
            input>>r>>g>>b;
            pixels[index].setRGB(r,g,b);
        }
    }
}

void PpmFile::readBinaryFile(File &other){

    char buffer[3];

    ifstream input(other.getFileName(),ios::binary);

    if(input){

        input.read(buffer,sizeof(char) * 3);
        int w,h,m;
        input>>w>>h>>m;
        this->setWidth(w);
        this->setHeight(h);
        this->setMaxColValue(m);
        this->pixels = new Pixel[width * height];
        unsigned char rgb[3];
        int sizeOfArray = this->width * this->height;
        std::cout<<sizeOfArray<<endl;
        for(int index = 0; index < sizeOfArray; ++index){

            input.read((char*)&rgb,3);
            pixels[index].setRGB(rgb[0],rgb[1],rgb[2]);
        }
    }

    input.close();
}

void PpmFile::convertToASCIIGrayScale(){

    ofstream input(newFileName, ios::binary);

   if(input){
        char buffer[] = "P3\n";
        input<<buffer;
        input<<this->getWidth()<<" "<<this->getHeight()<<endl<<this->maxColValue<<endl;
        int sizeOfImage = this->getWidth() * this->getHeight();
        for(int index = 0; index < sizeOfImage; ++index){

            int r,g,b;

            r = this->pixels[index].getRed();
            g = this->pixels[index].getGreen();
            b = this->pixels[index].getBlue();

            int gray = (r + g + b) / 3;
            r = gray;
            g = gray;
            b = gray;

            input<<r<<" "<<" "<<g<<" "<<b<<" ";

        }
    }

   input.close();
}

void PpmFile::convertToGrayscale(){

    char asd[] = "c:\\temp\\xmas_grayscale.ppm";
    ofstream input(asd, ios::binary);

    if(input){

        char buffer[] = "P6\n";
        input.write(buffer,sizeof(char) * 3);
        input<<this->getWidth()<<" "<<this->getHeight()<<endl<<this->maxColValue<<endl;
        int sizeOfImage = this->getWidth() * this->getHeight();
        unsigned char data[3];
        for(int index = 0; index < sizeOfImage; ++index){

            int r,g,b;

            r = this->pixels[index].getRed();
            g = this->pixels[index].getGreen();
            b = this->pixels[index].getBlue();

            int gray = (r + g + b) / 3;
            r = gray;
            g = gray;
            b = gray;
            data[0] = r;
            data[1] = g;
            data[2] = b;
           input.write((char*)&data,3);

        }
    }

   input.close();
}

void PpmFile::destroy(){

    delete [] this->pixels;
    delete [] this->newFileName;
}

