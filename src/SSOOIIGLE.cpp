/**************************************************************************
 * Project                : SSOOII Practice 2
 * 
 * 
 * Program Name           : SSOOIIGLE.cpp
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

#include "utils.cpp"
#include "threadFormat.cpp"

std::vector<ThreadFormat> g_vector_result;
std::vector<std::thread> g_vector_threads;

std::mutex g_mutex;

/*************************** Process Management **************************/
void parse_argv(int argc, char *argv[], int *n_thread, std::string *file_path, std::string *word);
void introMess();
void createThreads(int n_thread, int lines, std::string file_path, std::string word);
void search(int id_thread, std::string file_path, std::string word);
void assign_ff(std::vector<std::string> v_words_line, std::string word, int id, int i, int actual_line);
void waitThreads();
void showResult();



/*************************** Main Function **************************/
int main(int argc, char *argv[])
{
    int n_thread;
    std::string file_path;
    std::string word;

    parse_argv(argc, argv, &n_thread, &file_path, &word);
    introMess();
    int lines = countLine(file_path);
    std::cout << ANSI_COLOR_BLUE "Nº Lines: " << ANSI_COLOR_MAGENTA << lines << std::endl
              << ANSI_COLOR_BLUE "Nº Threads: " << n_thread << std::endl
              << ANSI_COLOR_BLUE "Word to search: " ANSI_COLOR_RED << word << ANSI_COLOR_BLUE << std::endl
              << ANSI_COLOR_BLUE "File to search: " ANSI_COLOR_RESET << PATH << ANSI_COLOR_BLUE << std::endl;
    createThreads(n_thread, lines, file_path, word);
    waitThreads();
    showResult();

    return EXIT_SUCCESS;
}



/*************************** Process Management **************************/

/*Whenever the current word matches the search word, 
then the ThreadFormat values are assigned and queued.*/
void assign_ff(std::vector<std::string> v_words_line, std::string word, int id, int i, int actual_line)
{
    FileFormat ff;

    if ((v_words_line.at(i).compare(word)) == 0)
    {
        if (i != 0)
        {
            ff.prev_word = v_words_line.at(i - 1);
        }
        else
        {
            ff.prev_word = " ";
        }

        if (i == v_words_line.size() - 1)
        {
            ff.post_word = " ";
        }
        else
        {
            ff.post_word = v_words_line.at(i + 1);
        }

        ff.word = v_words_line.at(i);
        ff.line = actual_line;

        std::lock_guard<std::mutex> lockguard(g_mutex);
        g_vector_result.at(id).wordMatch(ff);
    }
}

/*Transform everything to lower case, and divide by words.*/
void search(int id_thread, std::string file_path, std::string word)
{
    int start, end, i;
    int actual_line = 1;
    std::string prev_word, post_word;
    std::string line;
    std::ifstream is(file_path, std::ifstream::in);
    std::vector<std::string> v_words_line;
    FileFormat ff;
    int id = id_thread - 1;

    std::unique_lock<std::mutex> latch(g_mutex);
    start = g_vector_result.at(id).getStartLine();
    end = g_vector_result.at(id).getEndLine();
    latch.unlock();

    while (getline(is, line))
    {
        if (actual_line >= start && actual_line <= end)
        {
            std::transform(line.begin(), line.end(), line.begin(), ::tolower);
            v_words_line = splitIntoToken(line);
            for (i = 0; i < v_words_line.size(); i++)
            {
                assign_ff(v_words_line, word, id, i, actual_line);
            }
        }
        actual_line++;
    }
}

/*It defines the block that each thread will be in charge of and makes the call to the structure. 
Each structure created shall be stored in a global vector of threads.*/
void createThreads(int n_thread, int lines, std::string file_path, std::string word)
{
    int start_line, end_line, id_thread;
    int blockThread = lines / n_thread;

    for (int i = 0; i < n_thread; i++)
    {
        id_thread = i + 1; 
        start_line = (blockThread * i) + 1;
        end_line = blockThread * id_thread;

        ThreadFormat _threads(id_thread, start_line, end_line);

        std::unique_lock<std::mutex> latch(g_mutex);
        g_vector_result.push_back(_threads);
        latch.unlock();

        g_vector_threads.push_back(std::thread(search, id_thread, file_path, word));
    }

    std::cout << "Lines per thread: " << ANSI_COLOR_GREEN << blockThread << ANSI_COLOR_RESET << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void parse_argv(int argc, char *argv[], int *n_thread, std::string *file_path, std::string *word)
{

    std::fstream fs;

    if (argc != NUM_ARGV)
    {
        std::cout << ANSI_COLOR_RED "Error in arguments ./SSOOIIGLE <path_file> <word> <n_thread>\n" ANSI_COLOR_RESET;
        exit(EXIT_FAILURE);
    }

    if (!existFile(PATH))
    {
        std::cout << ANSI_COLOR_RED "File " << PATH << " does not exist" ANSI_COLOR_RESET << std::endl;
        exit(EXIT_FAILURE);
    }

    try
    {
        *n_thread = std::stoi(N_THREAD);
    }
    catch (std::exception e)
    {
        std::cout << ANSI_COLOR_RED << N_THREAD << ANSI_COLOR_RESET " is not a number" << std::endl;
        exit(EXIT_FAILURE);
    }

    *file_path = PATH;
    *word = WORD;
}

void introMess()
{
    std::string name = ANSI_COLOR_BLUE "SS" ANSI_COLOR_RED "O" ANSI_COLOR_YELLOW "O" ANSI_COLOR_BLUE "II" ANSI_COLOR_GREEN "GL" ANSI_COLOR_RED "E" ANSI_COLOR_RESET;
    std::string text = "Welcome to " + name + " developed by Álvaro Cerdá \n";
    std::cout << "*************************************************************\n";
    std::cout << text << std::endl;
}

void waitThreads()
{
    std::for_each(g_vector_threads.begin(), g_vector_threads.end(), std::mem_fn(&std::thread::join));
}

void showResult()
{
    for (int i = 0; i < g_vector_threads.size(); i++)
    {
        g_vector_result.at(i).print();
    }
}

