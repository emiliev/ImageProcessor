#include "PpmFile.h"


///
///конструктор по подразбиране
///
PpmFile::PpmFile():pixels(NULL)
{
    this->pixels = new Pixel[0];
    this->setHeight(0);
    this->setWidth(0);
    this->setMaxColValue(0);
}

///
///конструктор за общо ползване
///
PpmFile::PpmFile(char* otherFile):pixels(NULL){

    this->setFile(otherFile);
    this->readFile();
}

///
///копиращ конструктор
///
PpmFile::PpmFile(PpmFile const &other):pixels(NULL){

    copyFrom(other);
}

///
///предефиниран оператор за присвояване
///
PpmFile& PpmFile::operator=(PpmFile const &other){

    if(this != &other){

        copyFrom(other);
    }

    return *this;
}

///
///деструктор
///
PpmFile::~PpmFile()
{
    destroy();
}

///
///копираме съдържанието на other
///
void PpmFile::copyFrom(PpmFile const &other){

    this->setWidth(other.width);
    this->setHeight(other.height);
    this->setMaxColValue(other.maxColValue);
    this->setFile(other.fileName);
}


///
///продължаваме четенето на файла от потока
///
void PpmFile::readFile(){

    ifstream input(fileName, ios::binary);
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

///
///записваме съдържанието на файла
///
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

///
///конвертиране на изображението до скала на сивото
///
void PpmFile::convertToGrayscale(){

    char monochrome[] = "_grayscale";
    this->setNewFileName(fileName,monochrome);
    if(!isP3){

        this->binaryGrayscale();
    }
    else{

        this->asciiGrayscale();
   }
}

///
///конвертиране на изображението до монохромно
///
void PpmFile::convertToMonochrome(){

    char monochrome[] = "_monochrome";
    this->setNewFileName(fileName,monochrome);
    if(!isP3){

        this->binaryMonochrome();
    }
    else{

        this->asciiMonochrome();
    }

}

///
///вътрешна функция, чрез която конвертираме до монохромно изображение
///
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

///
///записване на монохромното изображение във текстов файл
///
void PpmFile::asciiMonochrome(){

    ofstream output(newFileName);
    if(output){

        int sizeOfImage = this->getWidth() * this->getHeight();
        startRecording(output);
        for(int index = 0; index < sizeOfImage; ++index){

            Pixel newPix = makeMonochrome(index,sizeOfImage);
            output<<newPix.getRed()<<" "<<newPix.getGreen()<<" "<<newPix.getBlue()<<" ";
        }
    }

    output.close();
}

///
///записване на монохромното изображение във бинарен файл
///
void PpmFile::binaryMonochrome(){

    ofstream output(newFileName, ios::binary);
    if(output){

        startRecording(output);
        int sizeOfImage = this->getWidth() * this->getHeight();
        unsigned char data[3];
        for(int index = 0; index < sizeOfImage; ++index){

            Pixel newPix = makeMonochrome(index,sizeOfImage);
            data[0] = newPix.getRed();
            data[1] = newPix.getGreen();
            data[2] = newPix.getBlue();
            output.write((char*)&data,sizeof(unsigned char) * 3);
        }
    }
}

///
///вътрешна функция, чрез която конвертираме до сиво изображение
///
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

///
///записване на 'сиво' изображение във текстов файл
///
void PpmFile::asciiGrayscale(){

    ofstream output(newFileName);
    if(output){

        startRecording(output);
        int sizeOfImage = this->getWidth() * this->getHeight();

        for(int index = 0; index < sizeOfImage; ++index){
            Pixel newPix = makeGrayscale(index);
            output<<newPix.getRed()<<" "<<newPix.getGreen()<<" "<<newPix.getBlue()<<" ";
        }
    }

    output.close();
}

///
///записване на 'сивото' изображние във бинарен файл
///
void PpmFile::binaryGrayscale(){

   ofstream output(newFileName, ios::binary);

    if(output){

        startRecording(output);
        int sizeOfImage = this->getWidth() * this->getHeight();
        unsigned char data[3];
        for(int index = 0; index < sizeOfImage; ++index){

            Pixel newPix = makeGrayscale(index);
            data[0] = newPix.getRed();
            data[1] = newPix.getGreen();
            data[2] = newPix.getBlue();
            output.write((char*)&data,3);
        }
    }

    output.close();
}

///
///избор на хистограма
///
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

///
///вътрешна функция, чрез която записваме хистограма
///
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

    this->setNewFileName(fileName,text);
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

///
///освобождаваме na памет
///
void PpmFile::destroy(){

    delete [] this->pixels;
    delete [] this->newFileName;
}

