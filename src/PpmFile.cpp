#include "PpmFile.h"



PpmFile::PpmFile():pixels(NULL)
{
    this->pixels = new Pixel[0];
    this->setHeight(0);
    this->setWidth(0);
    this->setMaxColValue(0);
}

PpmFile::PpmFile(File &otherFile):pixels(NULL){

    this->file = otherFile;
    this->readFile(otherFile);
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

void PpmFile::copyFrom(PpmFile const &other){

    this->setWidth(other.width);
    this->setHeight(other.height);
    this->setMaxColValue(other.maxColValue);
}


void PpmFile::readFile(File &file){

    ifstream input(file.getFileName(), ios::binary);
    if(input){

        startReading(input);
        this->pixels = new Pixel[width * height];
        if(strcmp(this->getFormat(),"P6") ==0){

            this->isP3 = false;
            this->readBinaryFile(input);
        }
        else{

            this->isP3 = true;
            this->readBinaryFile(input);
        }
    }

    input.close();
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

///tyka rabotim sega
Pixel PpmFile::makeMonochrome(int index, int sizeOfImage){

    int r,g,b;
    r = this->pixels[index].getRed();
    g = this->pixels[index].getGreen();
    b = this->pixels[index].getBlue();

    if((r + g + b) /3 < maxColValue / 2){
        r = 0;
        g = 0;
        b = 0;
    }
    else{
        r = maxColValue;
        g = maxColValue;
        b = maxColValue;
    }
    int redC = pixels[index].getRed() - r;
    int blueC = pixels[index].getBlue() - b;
    int greenC = pixels[index].getGreen() - g;

    if(index + 1 < sizeOfImage){
        int numRed = pixels[index + 1].getRed() + (redC * (7.0 / 16));
        int numGreen = pixels[index + 1].getGreen() + (greenC * (7.0 / 16));
        int numBlue = pixels[index + 1].getBlue() + (blueC * (7.0/ 16));
        pixels[index + 1].setRGB(numRed,numGreen,numBlue);
    }
    if(index - 1 + width < sizeOfImage){
        int numRed = pixels[index - 1 + width].getRed() + (redC * (3.0 / 16));
        int numGreen = pixels[index - 1 + width].getGreen() + (greenC *(3.0 / 16));
        int numBlue = pixels[index - 1 + width].getBlue() + (blueC * (3.0 / 16));
        pixels[index - 1 + width].setRGB(numRed,numGreen,numBlue);
    }
    if(index + width < sizeOfImage){
        int numRed = pixels[index + width].getRed() + (redC * (5.0 / 16));
        int numGreen = pixels[index + width].getGreen() + (greenC *(5.0 / 16));
        int numBlue = pixels[index + width].getBlue() + (blueC * (5.0/ 16));
        pixels[index + width].setRGB(numRed,numGreen,numBlue);
    }
    if(index + 1  + width< sizeOfImage){
        int numRed = pixels[index + 1  + width].getRed() + (redC * (1.0 / 16));
        int numGreen = pixels[index + 1  + width].getGreen() + (greenC * (1.0 / 16));
        int numBlue = pixels[index + 1  + width].getBlue() + (blueC * (1.0 / 16));
        pixels[index + 1  + width].setRGB(numRed,numGreen,numBlue);
    }

    return Pixel(r,g,b);
}

void PpmFile::asciiMonochrome(){

    ofstream output(newFileName);
    if(output){

        char buffer[] = "P3\n";
        output<<buffer;
        output<<this->getWidth()<<" "<<this->getHeight()<<endl<<this->maxColValue<<endl;
        int sizeOfImage = this->getWidth() * this->getHeight();
        for(int index = 0; index < sizeOfImage; ++index){

            Pixel newPix = makeMonochrome(index,sizeOfImage);
            output<<newPix.getRed()<<" "<<newPix.getGreen()<<" "<<newPix.getBlue()<<" ";
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

            Pixel newPix = makeMonochrome(index,sizeOfImage);
            data[0] = newPix.getRed();
            data[1] = newPix.getGreen();
            data[2] = newPix.getBlue();
            input.write((char*)&data,sizeof(unsigned char) * 3);
        }
    }
}

Pixel PpmFile::makeGrayscale(int index){

    int r,g,b;
    r = this->pixels[index].getRed();
    g = this->pixels[index].getGreen();
    b = this->pixels[index].getBlue();
    int gray = (r + g + b) / 3;
    r = gray;
    g = gray;
    b = gray;
    return Pixel(r,g,b);
}

void PpmFile::asciiGrayscale(){

    ofstream output(newFileName);
    if(output){

        char buffer[] = "P3\n";
        output<<buffer;
        output<<this->getWidth()<<" "<<this->getHeight()<<endl<<this->maxColValue<<endl;
        int sizeOfImage = this->getWidth() * this->getHeight();

        for(int index = 0; index < sizeOfImage; ++index){
            Pixel newPix = makeGrayscale(index);
            output<<newPix.getRed()<<" "<<newPix.getGreen()<<" "<<newPix.getBlue()<<" ";
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

            Pixel newPix = makeGrayscale(index);
            data[0] = newPix.getRed();
            data[1] = newPix.getGreen();
            data[2] = newPix.getBlue();
            input.write((char*)&data,3);
        }
    }

    input.close();
}

void PpmFile::makeHistogram(HistogramColors choice){

    switch(choice){

    case RED:
        char red[15];
        strcpy(red,"_histogram_red");
        std::cout<<red<<std::endl;
        histogram(red,choice);
        break;
    case GREEN:
        char green[17];
        strcpy(green,"_histogram_green");
        histogram(green,choice);
        break;
    case BLUE:
        char blue[16];
        strcpy(blue,"_histogram_blue");
        histogram(blue,choice);
        break;
    }
}

void PpmFile::histogram(char * text,HistogramColors choice){

    int colorArray[256] = {0};
    for(int index =0; index < width * height; ++index){
        int num;
        if(choice == RED){
            num = pixels[index].getRed();
        }
        else if(choice == GREEN){
            num = pixels[index].getGreen();
        }
        else{
            num = pixels[index].getBlue();
        }
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

    this->setNewFileName(file,text);
    ofstream output(newFileName);
    if(output){

        output<<"P3\n";
        output<<256<<" "<<100<<std::endl<<255<<std::endl;
        for(int row = 0; row < 100; ++row){

                for(int col = 0; col < 256; ++col){
                int r = 0 ,g = 0,b = 0;
                if(histogramArray[row][col] == 1){
                    if(choice == RED){

                        r = maxColValue;
                    }
                    else if(choice == GREEN){

                        g = maxColValue;
                    }
                    else{

                        b = maxColValue;
                    }
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
