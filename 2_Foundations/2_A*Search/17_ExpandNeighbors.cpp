#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>  // for sort

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

enum class State {kEmpty, kObstacle, kClosed, kPath};

const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

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

// Helper Function -> Compare the F values of two cells.
bool Compare(const std::vector<int> node1,const std::vector<int> node2){
    
    int node1_fval = node1.at(2) + node1.at(3);
        int node2_fval = node2.at(2) + node2.at(3);

    if(node1_fval > node2_fval)
        return true;
    else
        return false;
    
}

bool CheckValidCell(const int x, const int y, std::vector<std::vector<State> > &boardIn){
    bool on_grid_x = (x >= 0 && x < boardIn.size());
    bool on_grid_y = (y >= 0 && y < boardIn[0].size());
    if (on_grid_x && on_grid_y)
        return boardIn[x][y] == State::kEmpty;
    return false;
}
/**
 * Sort the two-dimensional vector of ints in descending order.
 */
void CellSort(vector<vector<int>> *v) {
    std::sort(v->begin(), v->end(), Compare);
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

void ExpandNeighbors(const vector<int> &current, std::vector<int> &goalIn, 
                    std::vector<std::vector<int>> &opennodesIn,
                    std::vector<std::vector<State> > &gridIn){

// Get current node's data.
  int x = current[0];
  int y = current[1];
  int g = current[2];

  // Loop through current node's potential neighbors.
  for (int i = 0; i < 4; i++) {
    int x2 = x + delta[i][0];
    int y2 = y + delta[i][1];

    // Check that the potential neighbor's x2 and y2 values are on the grid and not closed.
    if (CheckValidCell(x2, y2, gridIn)) {
      // Increment g value and add neighbor to open list.
      int g2 = g + 1;
      int h2 = Heuristic(x2, y2, goalIn.at(0), goalIn.at(1));
      AddToOpen(x2, y2, g2, h2, opennodesIn, gridIn);
    }
  }
}

/** 
 * Implementation of A* search algorithm
 */
std::vector<std::vector<State>> Search(std::vector<std::vector<State> > boardIn, 
                                        std::vector<int> initIn,
                                        std::vector<int> goalIn){

std::vector<std::vector<int>> opennodes_={};

// Initialize the starting node.
int x = initIn.at(0);
int y = initIn.at(1);
int g = 0;
int h = Heuristic(x, y, goalIn.at(0),goalIn.at(1));
AddToOpen(x, y, g, h, opennodes_, boardIn);

 // TODO: while open vector is non empty 
while(!opennodes_.empty()){
    // TODO: Sort the open list using CellSort, and get the current node.
    CellSort(&opennodes_);
    // TODO: Get the x and y values from the current node, and set grid[x][y] to kPath.
    auto current = opennodes_.back();
    opennodes_.pop_back();
    x = current[0];
    y = current[1];
    boardIn[x][y] = State::kPath;
    // TODO: Check if you've reached the goal. If so, return grid.
    if (x == goalIn.at(0) && goalIn.at(1)) {
        return boardIn;
    }
    // If we're not done, expand search to current node's neighbors.
    // ExpandNeighbors
    ExpandNeighbors(current, goalIn, opennodes_, boardIn);
    
    } //End while loop

  // We've run out of new nodes to explore and haven't found a path.
std::cout << "No path found!" << "\n";
return std::vector<vector<State>>{};
}


// --------------------------------------------------------------------------
// Tests
// --------------------------------------------------------------------------
void PrintVector(vector<int> v) {
  cout << "{ ";
  for (auto item : v) {
    cout << item << " ";
  }
  cout << "}" << "\n";
}

void PrintVectorOfVectors(vector<vector<int>> v) {
  for (auto row : v) {
    cout << "{ ";
    for (auto col : row) {
      cout << col << " ";
    }
    cout << "}" << "\n";
  }
}

void PrintVectorOfVectors(vector<vector<State>> v) {
  for (auto row : v) {
    cout << "{ ";
    for (auto col : row) {
      cout << CellString(col) << " ";
    }
    cout << "}" << "\n";
  }
}

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
  return;
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
    PrintVectorOfVectors(open);
    cout << "Solution open list is: " << "\n";
    PrintVectorOfVectors(solution_open);
    cout << "\n";
  } else if (grid != solution_grid) {
    cout << "failed" << "\n";
    cout << "\n";
    cout << "Your grid is: " << "\n";
    PrintVectorOfVectors(grid);
    cout << "\n";
    cout << "Solution grid is: " << "\n";
    PrintVectorOfVectors(solution_grid);
    cout << "\n";
  } else {
    cout << "passed" << "\n";
  }
  return;
}

void TestCompare() {
  cout << "----------------------------------------------------------" << "\n";
  cout << "Compare Function Test: ";
  vector<int> test_1 {1, 2, 5, 6};
  vector<int> test_2 {1, 3, 5, 7};
  vector<int> test_3 {1, 2, 5, 8};
  vector<int> test_4 {1, 3, 5, 7};
  if (Compare(test_1, test_2)) {
    cout << "failed" << "\n";
    cout << "\n" << "a = ";
    PrintVector(test_1);
    cout << "b = ";
    PrintVector(test_2);
    cout << "Compare(a, b): " << Compare(test_1, test_2) << "\n";
    cout << "Correct answer: 0" << "\n";
    cout << "\n";
  } else if (!Compare(test_3, test_4)) {
    cout << "failed" << "\n";
    cout << "\n" << "a = ";
    PrintVector(test_3);
    cout << "b = ";
    PrintVector(test_4);
    cout << "Compare(a, b): " << Compare(test_3, test_4) << "\n";
    cout << "Correct answer: 1" << "\n";
    cout << "\n";
  } else {
    cout << "passed" << "\n";
  }
  return;
}

void TestSearch() {
  cout << "----------------------------------------------------------" << "\n";
  cout << "Search Function Test (Partial): ";
  std::vector <int> goal = {4, 5};
  auto board = ReadBoardFile("1.board");
  
  std::cout.setstate(std::ios_base::failbit); // Disable cout
  auto output = Search(board, goal, goal);
  std::cout.clear(); // Enable cout

  vector<vector<State>> solution{{State::kEmpty, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kEmpty, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kEmpty, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kEmpty, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty, State::kObstacle, State::kPath}};

  if (output != solution) {
    cout << "failed" << "\n";
    cout << "Search(board, {4,5}, {4,5})" << "\n";
    cout << "Solution board: " << "\n";
    PrintVectorOfVectors(solution);
    cout << "Your board: " << "\n";
    PrintVectorOfVectors(output);
    cout << "\n";
  } else {
    cout << "passed" << "\n";
  }
  return;
}

void TestCheckValidCell() {
  cout << "----------------------------------------------------------" << "\n";
  cout << "CheckValidCell Function Test: ";
  vector<vector<State>> grid{{State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kClosed, State::kClosed, State::kEmpty, State::kEmpty, State::kObstacle, State::kEmpty}};

  if (CheckValidCell(0, 0, grid)) {
    cout << "failed" << "\n";
    cout << "\n" << "Test grid is: " << "\n";
    PrintVectorOfVectors(grid);
    cout << "Cell checked: (0, 0)" << "\n";
    cout << "\n";
  } else if (!CheckValidCell(4, 2, grid)) {
    cout << "failed" << "\n";
    cout << "\n" << "Test grid is: " << "\n";
    PrintVectorOfVectors(grid);
    cout << "Cell checked: (4, 2)" << "\n";
    cout << "\n";
  } else {
    cout << "passed" << "\n";
  }
  cout << "----------------------------------------------------------" << "\n";
}

void TestExpandNeighbors() {
  cout << "----------------------------------------------------------" << "\n";
  cout << "ExpandNeighbors Function Test: ";
  vector<int> current{4, 2, 7, 3};
  std::vector<int> goal = {4, 5};
  vector<vector<int>> open{{4, 2, 7, 3}};
  vector<vector<int>> solution_open = open;
  solution_open.push_back(vector<int>{3, 2, 8, 4});
  solution_open.push_back(vector<int>{4, 3, 8, 2});
  vector<vector<State>> grid{{State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kClosed, State::kClosed, State::kEmpty, State::kEmpty, State::kObstacle, State::kEmpty}};
  vector<vector<State>> solution_grid = grid;
  solution_grid[3][2] = State::kClosed;
  solution_grid[4][3] = State::kClosed;
  ExpandNeighbors(current, goal, open, grid);
  CellSort(&open);
  CellSort(&solution_open);
  if (open != solution_open) {
    cout << "failed" << "\n";
    cout << "\n";
    cout << "Your open list is: " << "\n";
    PrintVectorOfVectors(open);
    cout << "Solution open list is: " << "\n";
    PrintVectorOfVectors(solution_open);
    cout << "\n";
  } else if (grid != solution_grid) {
    cout << "failed" << "\n";
    cout << "\n";
    cout << "Your grid is: " << "\n";
    PrintVectorOfVectors(grid);
    cout << "\n";
    cout << "Solution grid is: " << "\n";
    PrintVectorOfVectors(solution_grid);
    cout << "\n";
  } else {
  	cout << "passed" << "\n";
  }
  cout << "----------------------------------------------------------" << "\n";
  return;
}
// ------------------------------------------------------------------------
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

    // Tests
    TestHeuristic();
    TestAddToOpen();
    TestCompare();
    TestSearch();
    TestCheckValidCell();
    TestExpandNeighbors();
}
