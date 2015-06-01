#include "PpmFile.h"



PpmFile::PpmFile():pixels(NULL), newFileName(NULL)
{
    this->pixels = new Pixel[0];
    this->setHeight(0);
    this->setWidth(0);
    this->setMaxColValue(0);

}

PpmFile::PpmFile(File &otherFile):pixels(NULL), newFileName(NULL){

    this->file = otherFile;
    this->readFile(otherFile);
    this->histogram();
}

PpmFile::PpmFile(PpmFile const &other):pixels(NULL), newFileName(NULL){

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

void PpmFile::setNewFileName(File &fileName, char* text){

    delete [] newFileName;

    int sizeOftext = strlen(text);
    int sizeOfFileName = strlen(fileName.getFileName());
    int sizeOfNewFileName = sizeOftext + sizeOfFileName + 1;

    newFileName = new char[sizeOfNewFileName];
    strcpy(newFileName,fileName.getFileName());
    for(int index = sizeOfFileName - 4; index <=sizeOfFileName; ++index){

        newFileName[index + sizeOftext] = newFileName[index];
    }

    for(int index = 0; index < sizeOftext; ++index){

        newFileName[index + sizeOfFileName - 4] = text[index];
    }
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

    char monochrome[] = "_grayscale";
    this->setNewFileName(file,monochrome);
    if(!isP3){

        this->binaryGrayscale();
    }
    else{

        this->asciiGrayscale();
   }
}

void PpmFile::convertToMonochrome(){

    char monochrome[] = "_monochrome";
    this->setNewFileName(file,monochrome);
    if(!isP3){

        this->binaryMonochrome();
    }
    else{

        this->asciiMonochrome();
    }

}

void PpmFile::asciiMonochrome(){

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

           if(r*g*b < 255 * 255 * 255 / 2 ){
                r = 255;
                g = 255;
                b = 255;
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

    switch(choice){

    case RED:

        break;
    case GREEN:

        break;
    case BLUE:

        break;
    }
}

void PpmFile::histogram(){

    int colorArray[256] = {0};
    for(int index =0; index < width * height; ++index){

        int num = pixels[index].getRed();
        colorArray[num]++;
    }
    int percent = width * height / 100;
    int  sum = 0;
    for(int index = 0; index < 256; ++index){
         int number = colorArray[index] / percent;
         sum +=number;
         colorArray[index] = number;
    }

    int histogramArray[100][256] = {0,};

    for(int col = 0; col < 256; ++col){

        int range = colorArray[col];
        for(int index = 0 ; index < range; ++index){

            histogramArray[99 - index][col] = 1;
        }
    }

    char text[] = "_histogram_red";
    this->setNewFileName(file,text);
    ofstream output(newFileName);
    if(output){

        output<<"P3\n";
        output<<256<<" "<<100<<std::endl<<255<<std::endl;
        for(int row = 0; row < 100; ++row){

                for(int col = 0; col < 256; ++col){
                int r ,g,b;
                if(histogramArray[row][col] == 1){
                    r = 255;
                    g = 0;
                    b = 0;
                }
                else{

                    r = maxColValue;
                    g = maxColValue;
                    b = maxColValue;
                }
                output<<r<<" "<<g<<" "<<b<<" ";
            }
        }
    }
}

void PpmFile::destroy(){

    delete [] this->pixels;
    delete [] this->newFileName;
}

