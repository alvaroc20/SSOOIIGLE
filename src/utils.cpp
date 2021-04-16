/**************************************************************************
 * Project                : SSOOII Practice 2
 * 
 * 
 * Program Name           : utils.cpp
 * 
 * 
 * Author                 : Álvaro Cerdá
 * 
 * 
 * Date Created           : 28/03/2021
 * 
 * 
 * Description            : Create a word search engine that divides the 
 *                          content of the file between several threads and 
 *                          distributes the workload. Store in a structure the searched word, 
 *                          the word before and after them and display them on the screen.
 * ************************************************************************/



#include "utils.h"
#include <sstream>
#include <string.h>
#include <algorithm>
#include <vector>

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

std::vector <std::string> splitIntoToken(std::string line)
{
    std::vector <std::string> v_words_line;
    std::stringstream check(line);
    std::string word;

    while(getline(check, word, ' ')){
        v_words_line.push_back(word);
    }

    return v_words_line;
}