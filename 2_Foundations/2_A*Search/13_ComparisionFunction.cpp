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

enum class State {kEmpty, kObstacle, kClosed};

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

// Helper Function -> COmparision
bool Compare(const std::vector<int> node1,const std::vector<int> node2){
    
    int node1_fval = node1.at(2) + node1.at(3);
        int node2_fval = node2.at(2) + node2.at(3);

    if(node1_fval > node2_fval)
        return true;
    else
        return false;
    
}

/**
 * Heuristics Function
 * @brief: It calculates manhatten distance
 */
int Heuristic(int x1, int y1, int x2, int y2){
    return (abs(x2-x1) + abs(y2-y1));
}

void AddToOpen(const int xIn,const int yIn,const int gIn,const int hIn, 
                vector<vector<int>> &openNodes,
                vector<vector<State> > &grid ){
        openNodes.push_back(vector<int>{xIn, yIn, gIn, hIn});
        grid[xIn][yIn] = State::kClosed;
}

/** 
 * Implementation of A* search algorithm
 */
std::vector<std::vector<State>> Search(std::vector<std::vector<State> > boardIn, 
                                        const std::vector<int> initIn,
                                        const std::vector<int> goalIn){

std::vector<std::vector<int>> opennodes_={};

// Initialize the starting node.
int x = initIn.at(0);
int y = initIn.at(1);
int g = 0;
int h = Heuristic(x, y, goalIn.at(0),goalIn.at(1));
AddToOpen(x, y, g, h, opennodes_, boardIn);

std::cout << "No path found!" << "\n";
return std::vector<vector<State>>{};
}


// --------------------------------------------------------------------------
// Tests
void TestHeuristic() {
    cout << "----------------------------------------------------------" << "\n";
    cout << "Heuristic Function Test: ";
    if (Heuristic(1, 2, 3, 4) != 4) {
    cout << "failed" << "\n";
    cout << "\n" << "Heuristic(1, 2, 3, 4) = " << Heuristic(1, 2, 3, 4) << "\n";
    cout << "Correct result: 4" << "\n";
    cout << "\n";
    } else if (Heuristic(2, -1, 4, -7) != 8) {
    cout << "TestHeuristic Failed" << "\n";
    cout << "\n" << "Heuristic(2, -1, 4, -7) = " << Heuristic(2, -1, 4, -7) << "\n";
    cout << "Correct result: 8" << "\n";
    cout << "\n";
    } else {
    cout << "passed" << "\n";
    }
    cout << "----------------------------------------------------------" << "\n";
}

void TestAddToOpen() {
  cout << "----------------------------------------------------------" << "\n";
  cout << "AddToOpen Function Test: ";
  int x = 3;
  int y = 0;
  int g = 5;
  int h = 7;
  vector<vector<int>> open{{0, 0, 2, 9}, {1, 0, 2, 2}, {2, 0, 2, 4}};
  vector<vector<int>> solution_open = open; 
  solution_open.push_back(vector<int>{3, 0, 5, 7});
  vector<vector<State>> grid{{State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kEmpty, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty, State::kObstacle, State::kEmpty}};
  vector<vector<State>> solution_grid = grid;
  solution_grid[3][0] = State::kClosed;
  AddToOpen(x, y, g, h, open, grid);
  if (open != solution_open) {
    cout << "failed" << "\n";
    cout << "\n";
    cout << "Your open list is: " << "\n";
    //PrintVectorOfVectors(open);
    cout << "Solution open list is: " << "\n";
    //PrintVectorOfVectors(solution_open);
    cout << "\n";
  } else if (grid != solution_grid) {
    cout << "failed" << "\n";
    cout << "\n";
    cout << "Your grid is: " << "\n";
    //PrintVectorOfVectors(grid);
    cout << "\n";
    cout << "Solution grid is: " << "\n";
    //PrintVectorOfVectors(solution_grid);
    cout << "\n";
  } else {
    cout << "passed" << "\n";
  }
  cout << "----------------------------------------------------------" << "\n";
  return;
}

// --------------------------------------------------------------------------
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
