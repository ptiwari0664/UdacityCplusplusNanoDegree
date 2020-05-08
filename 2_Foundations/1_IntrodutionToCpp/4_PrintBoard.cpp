#include <iostream>
#include <vector>

void PrintBoard(std::vector<std::vector<int>> vecIn){

    for(auto vec: vecIn){
        for(int i: vec){
            std::cout<< i<< " ";
        }
        std::cout<<"\n";
    }
}


int main() {

//INitializing vector
std::vector< std::vector<int> > board;
board = {{0, 1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0}};

// Printing the size of the 2Dvector
std::cout << board.size() << std::endl; //Will print no of rows
std::cout << board.at(0).size() << std::endl; //Will print no of columns

PrintBoard(board);
}
