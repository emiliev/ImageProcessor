#include "Image.h"

Image::Image()
{

}

Image::Image(File  &fileName){


}

Image::Image(const Image& other)
{

}

Image& Image::operator=(Image const &other){

    if(this != &other){


    }

    return *this;
}

Image::~Image()
{

}

/*
void Image::readFile(File &fileName){

    ifstream output(fileName.getFileName(),ios::binary);
    if(output){

        int w,h,m;
        char buffer[3];
        output.read(buffer,3);
        output>>w>>h>>m;
        this->setWidth(w);
        this->setHeight(h);
        this->setMaxColValue(m);
        this->pixels = new Pixel[w * h];
        unsigned char rgb[3];
        for(int index = 0; index < w * h; ++index){

            output.read((char*)&rgb,3);
            pixels[index].setRGB(rgb[0],rgb[1],rgb[2]);
        }
    }

    output.close();
}
*/
/*
void Image::convertToMonochrome(File &fileName){

    char monochrome[] = "_monochrome";
    int sizeOfMonochrome = strlen(monochrome);
    int sizeOfFile = strlen(fileName.getFileName());
    int sizeOfNewFile = sizeOfFile + sizeOfMonochrome + 1;
    char* newFileName = new char[sizeOfNewFile];
    strcpy(newFileName,fileName.getFileName());

    for(int index = strlen(fileName.getFileName()) - 4; index < strlen(fileName.getFileName()); ++index){

        newFileName[index + sizeOfMonochrome] = newFileName[index];
    }

    for(int index = 0 ;index <sizeOfMonochrome; ++index){
        newFileName[sizeOfFile - 4 + index] = monochrome[index];
    }

   ofstream input(newFileName, ios::binary);

   if(input){

        char buffer[] = "P6\n";
        input.write(buffer,sizeof(char) * 2);
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
*/
