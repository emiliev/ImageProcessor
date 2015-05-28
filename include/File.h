#ifndef FILE_H
#define FILE_H

#include <string.h>

class File
{
    public:
        File();
        File(char*);
        File(File const &);
        File& operator=(File const &);
        ~File();

        void setFileName(char* );
        char* getFileName();
    protected:
    private:

        char* fileName;
        void destroy();
        void copyFrom(File const &);

};

#endif // FILE_H
