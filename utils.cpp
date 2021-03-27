#include "utils.h"

bool existFile(std::string path)
{
    std::ifstream file(path);
    if(!file.is_open())
    {
        return false;
    }
    return true;
}


int countLine(std::string path)
{
    int line = 1;
    std::ifstream file(path);

    if(existFile(path))
    {
        while(!file.eof())
        {
            if(file.get()=='\n') 
                line++;
        }
    }
    return line;
}