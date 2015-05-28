#include "File.h"

File::File():fileName(NULL)
{
    fileName = new char[1];
    fileName[0] = '\0';

}

File::File(char* word):fileName(NULL){

    this->setFileName(word);
}

File::File(File const &other):fileName(NULL){

    copyFrom(other);
}

File& File::operator=(File const &other){

    if(this != &other){

        copyFrom(other);
    }

    return *this;
}

File::~File()
{
    destroy();
}

void File::setFileName(char* word){

    //destroy();
    int sizeOfWord = strlen(word) + 1;
    this->fileName = new char[sizeOfWord];
    strcpy(fileName,word);

}

char* File::getFileName(){

    return this->fileName;
}

void File::destroy(){

    delete [] this->fileName;
}

void File::copyFrom(File const &other){

    this->setFileName(other.fileName);
}
