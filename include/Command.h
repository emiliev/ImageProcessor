#ifndef COMMAND_H
#define COMMAND_H

class Command
{
    public:

        Command();
        Command(char**, int);
        Command(Command const &);
        Command& operator=(Command const &);
        ~Command();

        void setCommands(char**, int);
        char* getCommandName(int);
        int getNumberOfCommands();

    protected:
    private:

        char** commands;
        void destroy();
        void copyFrom(Command const &);
        int numberOfCommands;
        bool isValidCommand(char* word);
        bool isExistingCommand(char* word);
        void resizeCommands(char* word);

};

#endif // COMMAND_H
