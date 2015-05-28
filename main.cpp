#include <iostream>
#include <string.h>
#include "File.h"
#include "Command.h"
#include "Image.h"
#include "PpmFile.h"

using namespace std;

char ppm[] = ".ppm";
char pgm[] =".pgm";
char pbm[] = ".pbm";
char gray[] = "--grayscale";
char mono[] = "--monochrome";

int fileCounter = 0;
int commandCounter = 0;
bool isValidFile(char* word){

    char subWord[4];
    int wordLength = strlen(word);
    for(int index = 0; index <5; ++index){
        subWord[index] = word[wordLength - 4 + index];
    }

    if(strcmp(ppm,subWord) == 0 || strcmp(subWord,pgm) == 0 || strcmp(subWord,pbm) == 0){

        ++fileCounter;
        return true;
    }

    return false;
}

bool isValidCommand(char* word){

    if(strcmp(word,mono) == 0){

        commandCounter++;
        return true;
    }
    else if(strcmp(word,gray) == 0){

        commandCounter++;
        return true;
    }
    else{
        return false;
    }
}

int main(int argc, char* argv[])
{
   /* File* fileArray = new File[fileCounter];
    Command* commandArray = new Command[commandCounter];

    int fCounter = 0;
    int cCounter = 0;
    for(int index = 0; index < argc; ++index){

        if(isValidFile(argv[index])){
            File file1(argv[index]);
            fileArray[fCounter] = file1;
            std::cout<<fileArray[fCounter].getFileName()<<endl;
            fCounter++;
        }
        if(isValidCommand(argv[index])){
            Command command1(argv[index]);
            commandArray[cCounter] = command1;
            cCounter++;
        }
    }
*/
    char buffer[] = "c:\\temp\\xmas.ppm";
    File f1(buffer);
    PpmFile ppm(f1);

    return 0;
}
