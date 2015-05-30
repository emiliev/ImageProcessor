#include "PpmFile.h"



PpmFile::PpmFile():pixels(NULL)
{
    this->pixels = new Pixel[0];
    this->setHeight(0);
    this->setWidth(0);
    this->setMaxColValue(0);


}

PpmFile::PpmFile(File &otherFile):pixels(NULL){

    this->readFile(otherFile);
    this->getNewFileName(otherFile);

}

PpmFile::PpmFile(PpmFile const &other):pixels(NULL){

    copyFrom(other);
}

PpmFile& PpmFile::operator=(PpmFile const &other){

    if(this != &other){

        copyFrom(other);
    }

    return *this;
}

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
    this->setMaxColValue(other.maxColValue);
}

///zapochvam da cheta faila
void PpmFile::readFile(File &file){

    char buffer[2];
    ifstream input(file.getFileName(), ios::binary);

    if(input){

        input.read(buffer,sizeof(char) * 2);
        int w,h,m;
        input>>w>>h>>m;
        this->setWidth(w);
        this->setHeight(h);
        this->setMaxColValue(m);
        this->pixels = new Pixel[width * height];
        if(strcmp(buffer,"P6") ==0){
            std::cout<<"faila e p6!\n";
            this->isP3 = false;
            this->readBinaryFile(input);
        }
        else{

            std::cout<<"faila e p3!\n";
            this->isP3 = true;
            this->readBinaryFile(input);
        }
    }

    input.close();
}

char* PpmFile::getNewFileName(File &fileName){

    char grayscale[] = "_grayscale";
    int sizeOfGrayscale = strlen(grayscale);
    int sizeOfFile = strlen(fileName.getFileName());
    int sizeOfNewFile = sizeOfFile + sizeOfGrayscale + 1;
    newFileName = new char[sizeOfNewFile];
    strcpy(newFileName,fileName.getFileName());

    for(int index = sizeOfFile - 4; index <= sizeOfFile; ++index){

        newFileName[index + sizeOfGrayscale] = newFileName[index];
    }

    for(int index = 0 ;index <sizeOfGrayscale; ++index){
        newFileName[sizeOfFile - 4 + index] = grayscale[index];
    }

    return newFileName;
}

void PpmFile::readBinaryFile(ifstream &input){

    int sizeOfArray = this->width * this->height;
        if(input){
            ///read as binary
            if(!isP3){

                unsigned char rgb[3];
                for(int index = 0; index < sizeOfArray; ++index){

                    input.read((char*)&rgb,3);
                    pixels[index].setRGB(rgb[0],rgb[1],rgb[2]);
                }
            }

            ///read as txt
            else{

                int r,g,b;
                for(int index = 0; index <sizeOfArray; ++index){

                    input>>r>>g>>b;
                    pixels[index].setRGB(r,g,b);
                }
            }
    }
    input.close();
}

void PpmFile::convertToGrayscale(){

    if(!isP3){

        this->binaryGrayscale();
    }
    else{

        this->asciiGrayscale();
   }
}

void PpmFile::convertToMonochrome(){

    if(!isP3){

        this->binaryMonochrome();
    }
    else{

        this->asciiMonochrome();
    }

}

void PpmFile::asciiMonochrome(){

    char asd[] = "c:\\temp\\asdasdasd_monochrome.ppm";
    ofstream output(asd);
    if(output){

        char buffer[] = "P3\n";
        output<<buffer;
        output<<this->getWidth()<<" "<<this->getHeight()<<endl<<this->maxColValue<<endl;
        int sizeOfImage = this->getWidth() * this->getHeight();
        for(int index = 0; index < sizeOfImage; ++index){

            int r,g,b;

            r = this->pixels[index].getRed();
            g = this->pixels[index].getGreen();
            b = this->pixels[index].getBlue();

           if(r*g*b < 127 * 127 * 127){
                r = maxColValue;
                g = maxColValue;
                b = maxColValue;
            }
            else{
                r = 0;
                g = 0;
                b = 0;
            }

            output<<r<<" "<<g<<" "<<b<<" ";

        }
    }

    output.close();
}

void PpmFile::binaryMonochrome(){

    char asd[] = "c:\\temp\\asdasdasd_monochrome.ppm";
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

           if(r*g*b < 127 * 127 * 127){
                r = maxColValue;
                g = maxColValue;
                b = maxColValue;
            }
            else{
                r = 0;
                g = 0;
                b = 0;
            }

            data[0] = r;
            data[1] = g;
            data[2] = b;
            input.write((char*)&data,sizeof(unsigned char) * 3);
        }
    }
}

void PpmFile::asciiGrayscale(){

    ofstream output(newFileName);
    if(output){

        char buffer[] = "P3\n";
        output<<buffer;
        output<<this->getWidth()<<" "<<this->getHeight()<<endl<<this->maxColValue<<endl;
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

            output<<r<<" "<<g<<" "<<b<<" ";

        }
    }

    output.close();
}

void PpmFile::binaryGrayscale(){

   ofstream input(newFileName, ios::binary);

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

void PpmFile::makeHistogram(HistogramColors choice){

}

void PpmFile::destroy(){

    delete [] this->pixels;
    delete [] this->newFileName;
}

