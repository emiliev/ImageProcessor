#include "Pixel.h"

Pixel::Pixel()
{
   this->setRGB(0,0,0);
}

Pixel::Pixel(int r,int g,int b){

    this->setRGB(r,g,b);
}

Pixel::Pixel(Pixel const &other){

    copyFrom(other);
}

Pixel& Pixel::operator=(Pixel const &other){

    if(this != &other){

        copyFrom(other);
    }

    return *this;
}

Pixel::~Pixel()
{

}

void Pixel::setRGB(int r, int g,int b){

    this->red = r;
    this->green = g;
    this->blue = b;
}

int Pixel::getRed(){

    return this->red;
}


int Pixel::getBlue(){

    return this->blue;
}


int Pixel::getGreen(){

    return this->green;
}

void Pixel::copyFrom(Pixel const &other){

    this->setRGB(other.red,other.green,other.blue);
}
