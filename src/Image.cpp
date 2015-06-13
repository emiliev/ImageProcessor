#include "Image.h"

Image::Image()
{

}

Image::Image(char* file){


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

///
/// ��������
///
int Image::getHeight(){

    return this->height;
}

///
/// ��������
///
int Image::getWidth(){

    return this->width;
}

///
/// ��������
///
int Image::getMaxColValue(){

    return this->maxColValue;
}

///
///�������
///
void Image::setHeight(int h){

    this->height = h;
}

///
///�������
///
void Image::setWidth(int w){

    this->width = w;
}

///
///�������
///
void Image::setMaxColValue(int m){

    this->maxColValue = m;
}

///
///������� �������� �� ����� �� ������
///
void Image::startRecording(ofstream &output){


        output<<format<<endl;
        output<<this->getWidth()<<" "<<this->getHeight()<<endl;
        if(!(compareFormat("P1") && compareFormat("P3"))){

            output<<this->maxColValue<<endl;
        }
}

///
///������� ����������� �� ��� ����
///
void Image::startReading(ifstream &input){

    if(input){

        input>>format;
        int w,h,m;
        input>>w>>h;
        if(!(compareFormat("P1") && compareFormat("P3"))){

            input>>m;
            this->setMaxColValue(m);
        }
        this->setWidth(w);
        this->setHeight(h);
    }
}

///
///���������� format � text
///
bool Image::compareFormat(char* text){

    if(strcmp(format,text) == 0){

        return true;
    }
    return false;
}

///
///��������
///
char* Image::getFormat(){

    return this->format;
}

///
///�������
///
void Image::setNewFileName(char* file, char* text){

    int sizeOftext = strlen(text);
    int sizeOfFileName = strlen(file);
    int sizeOfNewFileName = sizeOftext + sizeOfFileName + 1;

    newFileName = new char[sizeOfNewFileName];
    strcpy(newFileName,file);
    for(int index = sizeOfFileName - 4; index <=sizeOfFileName; ++index){

        newFileName[index + sizeOftext] = newFileName[index];
    }

    for(int index = 0; index < sizeOftext; ++index){

        newFileName[index + sizeOfFileName - 4] = text[index];
    }
}

void Image::setFile(char* file){

    int length = strlen(file) + 1;
    fileName = new char[length];
    strcpy(fileName,file);
}
