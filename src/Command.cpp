#include "Command.h"
#include <string.h>
#include <iostream>


///
///конструктор по подразбиране
///
Command::Command():commands(NULL), numberOfCommands(0)
{
    this->commands = new char*[1];
    this->commands[0] = '\0';
}

///
///конструктор за общо ползване
///
Command::Command(char** word, int allWords):commands(NULL){

    numberOfCommands = 0;
    setCommands(word, allWords);
}

///
///предефиниция на оператора за присвояване
///
Command& Command::operator=(Command const &other){

    if(this != &other){

        copyFrom(other);
    }

    return *this;
}

///
///копиращ конструктор
///
Command::Command(Command const &other):commands(NULL){

    copyFrom(other);
}

///
///деструктор
///
Command::~Command()
{
    destroy();
}

///
///освобждаваме паметта на член данната
///
 void Command::destroy(){

    for(int index = 0; index < numberOfCommands; ++index){
            delete [] this->commands[index];
    }

    delete [] commands;
}

///
///преоразмеряване на масива
///
void Command::resizeCommands(char* word){

    numberOfCommands++;
    char** newCommands = new char*[numberOfCommands];
    for(int index = 0; index < numberOfCommands - 1; ++index){

        int length = strlen(commands[index]) + 1;
        newCommands[index] = new char[length];
        strcpy(newCommands[index],commands[index]);
    }

    int lastSize = strlen(word) + 1;
    newCommands[numberOfCommands - 1] = new char[lastSize];
    strcpy(newCommands[numberOfCommands - 1], word);

    for(int index = 0; index < numberOfCommands - 1; ++index){

        delete [] commands[index];
    }

    delete [] commands;
    commands = newCommands;

}

///
///проверка дали съществува такава команда в масива
///
bool Command::isExistingCommand(char* word){

    for(int index = 0; index < numberOfCommands; ++index){

        if(strcmp(word,commands[index]) == 0){
            return true;
        }
    }
    return false;
}

///
///мутатор
///
void Command::setCommands(char** word, int allWords){

    std::cout<<allWords<<std::endl;
    for(int index = 0; index < allWords; ++index){

        if(isValidCommand(word[index])){
            if(!isExistingCommand(word[index])){
                resizeCommands(word[index]);
            }
        }
    }
}

///
///селектор
///
char* Command::getCommandName(int index){
    if(index < numberOfCommands){
        return this->commands[index];
    }
    else{

        return this->commands[0];
    }
}

int Command::getNumberOfCommands(){

    return this->numberOfCommands;
}

///
///копираме съдържанието на other
///
void Command::copyFrom(Command const &other){

    this->numberOfCommands = other.numberOfCommands;
    this->setCommands(other.commands, other.numberOfCommands);
}

///
///Проверяваме дали думата е валидна команда
///
bool Command::isValidCommand(char* word){

    char gray[] = "--grayscale";
        char mono[] = "--monochrome";
        char histogramRed[] = "--histogram=red";
        char histogramGreen[] = "--histogram=green";
        char histogramBlue[] = "--histogram=blue";

    if(strcmp(word,mono) == 0){

        return true;
    }
    else if(strcmp(word,histogramBlue) == 0){

        return true;
    }
    else if(strcmp(word,histogramRed) == 0){

        return true;
    }
    else if(strcmp(word,histogramGreen) == 0){

        return true;
    }
    else if(strcmp(word,gray) == 0){

       return true;
    }
    else{
        return false;
    }
}
