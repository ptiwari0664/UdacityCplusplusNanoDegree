#include <fstream>
#include <iostream>
#include <string>

#ifdef WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

std::string get_working_path() {
    char cwd[1024];
    if (GetCurrentDir(cwd, sizeof(cwd)) != NULL)
        return std::string(cwd);
    else
        return std::string("");
}

int main()
{   
    //Method:1 
    std::ifstream my_file ("files/1.board");
    
    //Method:2
    //std::ifstream my_file;
    //my_file.open("files/1.board");
    
    if (my_file.is_open()) {
        std::cout << "The file stream has been created!" << "\n";
        
        std::string line;
        while (getline(my_file, line)) {
            std::cout << line << "\n";
        }
        my_file.close();
    }  
    else
    {
        std::cout << "File not found in cwd: " << get_working_path();
    }

}