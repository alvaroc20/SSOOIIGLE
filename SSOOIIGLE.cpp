#include "utils.cpp"
#include "colorText.h"

void parse_argv(int argc)
{
    if(argc != NUM_ARGV)
    {
        std::cout << ANSI_COLOR_RED "Error in arguments ./SSOOIIGLE <path_file> <word> <n_thread>\n" ANSI_COLOR_RESET;
    }
}


void welcomeMessage()
{
    std::string name = ANSI_COLOR_BLUE "SS" ANSI_COLOR_RED "O" ANSI_COLOR_YELLOW "O" ANSI_COLOR_BLUE "II" ANSI_COLOR_GREEN "GL" ANSI_COLOR_RED "E" ANSI_COLOR_RESET;
    std::string text = "Welcome to " + name+ " developed by Álvaro Cerdá \n";
    std::cout << "*************************************************************\n";
    std::cout << text << "\n\n";
}


int main(int argc, char *argv[])
{   
    welcomeMessage();
    parse_argv(argc);

    int lines = countLine(argv[1]);
    std::cout << "Nº Lineas: " << lines << "\n";

    return EXIT_SUCCESS;
}
