#include "File.h"

///
///����������� �� ������������
///
File::File():fileName(NULL)
{
    fileName = new char[1];
    fileName[0] = '\0';

}

///
///����������� �� ���� ��������
///
File::File(char* word):fileName(NULL){

    this->setFileName(word);
}

///
///���� �����������
///
File::File(File const &other):fileName(NULL){

    copyFrom(other);
}

///
/// �������� =
///
File& File::operator=(File const &other){

    if(this != &other){

        copyFrom(other);
    }

    return *this;
}

///
///����������
///
File::~File()
{
    destroy();
}

///
///�������
///
void File::setFileName(char* word){

    int sizeOfWord = strlen(word) + 1;
    this->fileName = new char[sizeOfWord];
    strcpy(fileName,word);
}

///
///��������
///
char* File::getFileName(){

    return this->fileName;
}

///
///������������� �������, �������� �� fileName
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
///����������� ���� ������� ��� � ������� ����
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
