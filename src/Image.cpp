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


int Image::getHeight(){

    return this->height;
}

int Image::getWidth(){

    return this->width;
}

int Image::getMaxColValue(){

    return this->maxColValue;
}

void Image::setHeight(int h){

    this->height = h;
}

void Image::setWidth(int w){

    this->width = w;
}

void Image::setMaxColValue(int m){

    this->maxColValue = m;
}

void Image::setNewFileName(File &fileName, char* text){

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


