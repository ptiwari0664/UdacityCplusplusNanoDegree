#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;
using std::abs;

#ifdef WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

enum class State {kEmpty,kObstacle};

std::string get_working_path() {
    char cwd[1024];
    if (GetCurrentDir(cwd, sizeof(cwd)) != NULL)
        return std::string(cwd);
    else
        return std::string("");
}

std::string CellString(State cell) {
    switch(cell) {
        case State::kObstacle: return "⛰️   ";
        default: return "0   "; 
    }
}

void PrintBoard(const std::vector<std::vector<State> > board) {
    for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
        std::cout << CellString(board[i][j]);
    }
    std::cout << "\n";
    }
}

std::vector<State> parseLine(std::string lineIn){
    std::istringstream my_stream(lineIn);
    
    char c;
    int n;
    std::vector<State> row_vec;
    while (my_stream >> n >> c && c==',') {
        // std::cout << "That stream was successful:" << n << " " << c << "\n";
        if(n==0)
            row_vec.push_back(State::kEmpty);
        else
            row_vec.push_back(State::kObstacle);
    }
    // std::cout << "The stream has failed." << "\n";
    return row_vec;
}

std::vector<std::vector <State> > ReadBoardFile(std::string pathIn){
    std::ifstream my_file (pathIn.c_str());

    std::vector<std::vector <State> > temp_double{};

    if (my_file.is_open()) {
        std::cout << "The file stream has been created!" << "\n";
        
        std::string line;
        std::vector<State> temp{};
        while (getline(my_file, line)) {
            // std::cout << line << "\n";
            temp = parseLine(line);
            temp_double.push_back(temp);
        }
        my_file.close();
    }  
    else
    {
        std::cout << "File not found in cwd: " << get_working_path();
    }

    return temp_double;
}

/** 
 * Implementation of A* search algorithm
 */
std::vector<std::vector<State>> Search(const std::vector<std::vector<State> > boardIn, 
                                        const std::vector<int> initIn,
                                        const std::vector<int> goalIn){

std::vector<std::vector<State>> board_={};


return board_;
}

/** 
 * Main Function
 */
int main() {
    // TODO: Declare "init" and "goal" arrays with values {0, 0} and {4, 5} respectively.
    std::vector<int> initPose = {0,0};
    std::vector<int> goalPose = {4,5};

    std::string path = "files/1.board";
    auto board = ReadBoardFile(path);
    PrintBoard(board); //Print intial maze
    
    // TODO: Call Search with "board", "init", and "goal". Store the results in the variable "solution".
    std::vector<std::vector <State> > solutionBoard = {};
    solutionBoard = Search(board,initPose,goalPose);
    // TODO: Change the following line to pass "solution" to PrintBoard.
    PrintBoard(solutionBoard);
}
