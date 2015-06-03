#include <iostream>
#include <fstream>
#include <string.h>
#include "File.h"
#include "Command.h"
#include "Image.h"
#include "PpmFile.h"
#include "PgmFile.h"
#include "PbmFile.h"

using namespace std;

char ppm[] = ".ppm";
char pgm[] =".pgm";
char pbm[] = ".pbm";
char gray[] = "--grayscale";
char mono[] = "--monochrome";
char histogramRed[] = "--histogram=red";
char histogramGreen[] = "--histogram=green";
char histogramBlue[] = "--histogram=blue";

bool isValidFile(char* word){

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

char* getLastSymbols(char* word){

    char subWord[4];
    int counter = 0;
    int length = strlen(word);
    if(length > 4){
        for(int index = length - 4; index <= length; ++index){

            subWord[counter] = word[index];
            counter++;
        }
    }

    return subWord;
}

bool isValidCommand(char* word){

    if(strcmp(word,mono) == 0){

        return true;
    }
    if(strcmp(word,histogramBlue) == 0){

        return true;
    }
    if(strcmp(word,histogramRed) == 0){

        return true;
    }
    if(strcmp(word,histogramGreen) == 0){

        return true;
    }
    else if(strcmp(word,gray) == 0){

        return true;
    }
    else{
        return false;
    }
}

int main(int argc, char* argv[])
{
    int fCounter = 0;
    int cCounter = 0;
    for(int index = 0; index < argc; ++index){

        if(isValidFile(argv[index])){
            fCounter++;
        }
        if(isValidCommand(argv[index])){

            cCounter++;
        }
    }

    int fileCounter = 0;
    int commandCounter = 0;
    File *fileArray = new File[fCounter];
    Command *commandArray = new Command[cCounter];
    for(int index = 0; index < argc; ++index){

        if(isValidFile(argv[index])){

            fileArray[fileCounter] = argv[index];
            std::cout<<"file: "<<fileArray[fileCounter].getFileName()<<std::endl;
            fileCounter++;
        }

        if(isValidCommand(argv[index])){

            commandArray[commandCounter] = argv[index];
            cout<<"command: "<<commandArray[commandCounter].getCommandName()<<std::endl;
            commandCounter++;
        }
    }

    Image *img[fileCounter];
    for(int index = 0; index < fileCounter; ++index){
        if(strcmp(getLastSymbols(fileArray[index].getFileName()),ppm) == 0){

             img[index] = new PpmFile(fileArray[index]);

        }
        else if(strcmp(getLastSymbols(fileArray[index].getFileName()),pgm) == 0){

            img[index] = new PgmFile(fileArray[index]);
        }
        else if(strcmp(getLastSymbols(fileArray[index].getFileName()),pbm) == 0 ){

            img[index] = new PbmFile(fileArray[index]);
        }

        for(int elem = 0; elem < commandCounter; ++elem){

            if(strcmp(commandArray[elem].getCommandName(),gray) == 0){

                img[index]->convertToGrayscale();
            }

            if(strcmp(commandArray[elem].getCommandName(),mono) == 0){

                img[index]->convertToMonochrome();
            }

             if(strcmp(commandArray[elem].getCommandName(),histogramRed) == 0){

                img[index]->makeHistogram(RED);
            }
             if(strcmp(commandArray[elem].getCommandName(),histogramGreen) == 0){

                img[index]->makeHistogram(GREEN);
            }
             if(strcmp(commandArray[elem].getCommandName(),histogramBlue) == 0){

                img[index]->makeHistogram(BLUE);
            }
        }
    }

    return 0;
}
