#ifndef COMMAND_H
#define COMMAND_H

class Command
{
    public:
        Command();
        Command(char*);
        Command(Command const &);
        Command& operator=(Command const &);
        ~Command();

        void setCommandName(char*);
        char* getCommandName();

    protected:
    private:

        char* commandName;
        void destroy();
        void copyFrom(Command const &);
};

#endif // COMMAND_H
