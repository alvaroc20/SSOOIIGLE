/**************************************************************************
 * Project                : SSOOII Practice 2
 * 
 * 
 * Program Name           : utils.h
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
#include <thread>
#include <mutex>
#include <string>
#include <fstream>
#include <algorithm>
#include <functional>

#define NUM_ARGV 4

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define PATH argv[1]
#define WORD argv[2]
#define N_THREAD argv[3]