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

    const char gray[] = "--grayscale";
    const char mono[] = "--monochrome";
    const char histogramRed[] = "--histogram=red";
    const char histogramGreen[] = "--histogram=green";
    const char histogramBlue[] = "--histogram=blue";
    char ppm[] = ".ppm";
    char pgm[] =".pgm";
    char pbm[] = ".pbm";

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

Image* newImage(int index, File *fileArray){

    ifstream input(fileArray[index].getFileName());
    if(input){

        char buffer[2];
        input>>buffer;
        if(strcmp(buffer, "P6") == 0 || strcmp(buffer, "P3") == 0){

            return new PpmFile(fileArray[index].getFileName());

        }
        else if(strcmp(buffer, "P5") == 0 || strcmp(buffer, "P2") == 0){

            return new PgmFile(fileArray[index].getFileName());
        }
        else if(strcmp(buffer, "P4") == 0 || strcmp(buffer, "P1") == 0){

            return new PbmFile(fileArray[index].getFileName());
        }
    }

    return NULL;
}

int main(int argc, char* argv[])
{

    int fCounter = 0;
    for(int index = 0; index < argc; ++index){

        if(isValidFile(argv[index])){
            fCounter++;
        }
      }

    int fileCounter = 0;
    File *fileArray = new File[fCounter];

    Command commandArray(argv, argc);

    for(int index = 0; index < argc; ++index){

        if(isValidFile(argv[index])){

            fileArray[fileCounter] = argv[index];
            std::cout<<"file: "<<fileArray[fileCounter].getFileName()<<std::endl;
            fileCounter++;
        }
    }

    Image *img[fileCounter];
    for(int index = 0; index < fileCounter; ++index){

        img[index] = newImage(index,fileArray);

        ///proverka dali obekta ne e NULL
        if(img[index] == NULL){

            continue;
        }
        for(int elem = 0; elem < commandArray.getNumberOfCommands(); ++elem){

            if(strcmp(commandArray.getCommandName(elem),gray) == 0){

                img[index]->convertToGrayscale();
            }

            if(strcmp(commandArray.getCommandName(elem),mono) == 0){

                img[index]->convertToMonochrome();
            }

             if(strcmp(commandArray.getCommandName(elem),histogramRed) == 0){

                img[index]->makeHistogram(RED);
            }
             if(strcmp(commandArray.getCommandName(elem),histogramGreen) == 0){

                img[index]->makeHistogram(GREEN);
            }
             if(strcmp(commandArray.getCommandName(elem),histogramBlue) == 0){

                img[index]->makeHistogram(BLUE);
            }
        }
    }

    for(int index = 0; index < fCounter; ++index){

        delete img[index];
    }
}
