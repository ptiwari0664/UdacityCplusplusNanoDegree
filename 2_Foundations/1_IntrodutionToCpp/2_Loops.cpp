#include <iostream>
#include <vector>

int main() {
    // Add your code here.
    for(int i=-3;i<11;i++){
        std::cout << i << "\n";
    }

    std::cout << "--------------------\n";
    
    //For Loop with a Container (Range based)
    std::vector<int> a {1, 2, 3, 4, 5};
    for (int i: a) {
        std::cout << i << "\n";
    }

    std::cout << "--------------------\n";

    // Double range based loop.
    std::vector<std::vector<int>> b {{1, 2},
                                    {3, 4},
                                    {5, 6}};

    // Write your double loop here.
    for(auto rowvec: b){
        for(int i: rowvec)
        {
            //COlumn print
            std::cout << i << " ";
        }
        //row print
        std::cout << "\n";
    }
}