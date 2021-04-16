/**************************************************************************
 * Project                : SSOOII Practice 2
 * 
 * 
 * Program Name           : threadFormat.cpp
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
#include "threadFormat.h"
#include "utils.h"


ThreadFormat::ThreadFormat(int id, int start, int end)
{
    this -> id = id;
    this -> start_line = start;
    this -> end_line = end;
}


int ThreadFormat::getStartLine()
{
    return start_line;
}

int ThreadFormat::getEndLine()
{
    return end_line;
}

void ThreadFormat::showResult(FileFormat ff)
{
    std::cout << ANSI_COLOR_GREEN"[Thread " << id << " Start: " << start_line << " - Final: " << end_line << "]" ANSI_COLOR_RESET;
    std::cout << ANSI_COLOR_MAGENTA" :: Line " << ff.line << " ... " ANSI_COLOR_YELLOW<< ff.prev_word << " " ANSI_COLOR_RED<< ff.word << " " ANSI_COLOR_YELLOW<< ff.post_word << " ..." ANSI_COLOR_RESET<< std::endl;
}

void ThreadFormat::wordMatch(FileFormat ff)
{
    queue.push(ff);
}

void ThreadFormat::print()
{
    while(!queue.empty()){
        showResult(queue.front());
        queue.pop();
    }
}

