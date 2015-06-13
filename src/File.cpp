#include "File.h"

///
///конструктор по подразбиране
///
File::File():fileName(NULL)
{
    fileName = new char[1];
    fileName[0] = '\0';

}

///
///конструктор за общо ползване
///
File::File(char* word):fileName(NULL){

    this->setFileName(word);
}

///
///копи конструктор
///
File::File(File const &other):fileName(NULL){

    copyFrom(other);
}

///
/// оператор =
///
File& File::operator=(File const &other){

    if(this != &other){

        copyFrom(other);
    }

    return *this;
}

///
///деструктор
///
File::~File()
{
    destroy();
}

///
///мутатор
///
void File::setFileName(char* word){

    int sizeOfWord = strlen(word) + 1;
    this->fileName = new char[sizeOfWord];
    strcpy(fileName,word);
}

///
///селектор
///
char* File::getFileName(){

    return this->fileName;
}

///
///освобождаваме паметта, заделена за fileName
///
void File::destroy(){

    delete [] this->fileName;
}

///
///
///
void File::copyFrom(File const &other){

    this->setFileName(other.fileName);
}


///
///ѕровер€ваме дали дадени€ низ е валиден файл
///
bool File::isValidFile(char* word){

    char ppm[] = ".ppm";
    char pgm[] =".pgm";
    char pbm[] = ".pbm";

    char subWord[4];
    int wordLength = strlen(word);
    for(int index = 0; index <5; ++index){
        subWord[index] = word[wordLength - 4 + index];
    }

    if(strcmp(ppm,subWord) == 0 || strcmp(subWord,pgm) == 0 || strcmp(subWord,pbm) == 0){

        return true;
    }

    return false;
}
