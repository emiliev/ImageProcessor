#ifndef COMMANDLINE_H_INCLUDED
#define COMMANDLINE_H_INCLUDED

class CommandLine{

    public:
    virtual void destroy() = 0;
    virtual void copyFrom(CommandLine const &) = 0;

};


#endif // COMMANDLINE_H_INCLUDED
