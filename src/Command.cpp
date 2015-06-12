#include "Command.h"

#include <string.h>

Command::Command():commandName(NULL)
{
    this->commandName = new char[1];
    this->commandName[0] = '\0';
}

Command::Command(char* word):commandName(NULL){

    setCommandName(word);
}

Command& Command::operator=(Command const &other){

    if(this != &other){

        copyFrom(other);
    }

    return *this;
}

Command::Command(Command const &other):commandName(NULL){

    copyFrom(other);
}

Command::~Command()
{
    destroy();
}

 void Command::destroy(){

    delete [] this->commandName;
}

void Command::setCommandName(char* word){

    int sizeOfCommand = strlen(word) + 1;
    this->commandName = new char[sizeOfCommand];
    strcpy(this->commandName,word);
}

char* Command::getCommandName(){

    return this->commandName;
}

void Command::copyFrom(Command const &other){

    this->setCommandName(other.commandName);
}

