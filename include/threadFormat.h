/**************************************************************************
 * Project                : SSOOII Practice 2
 * 
 * 
 * Program Name           : threadFormat.h
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


#include <iostream>
#include <queue>
#include <string>

struct FileFormat
{
    int line;
    std::string prev_word;
    std::string post_word;
    std::string word;
};

class ThreadFormat
{
    private:
        int id;
        int start_line;
        int end_line;
        std::queue<FileFormat> queue;

    public:
        ThreadFormat(int id, int start_line, int end_line);
        int getID();
        int getStartLine();
        int getEndLine();
        void showResult(FileFormat ff);
        void wordMatch(FileFormat ff);
        void print();
};