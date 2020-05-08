#include <iostream>
#include <vector>

// Function declared and defined here.
int AdditionFunction(int i, int j) {
    return i + j;
}

int vectorAddition(std::vector<int> vecIn){
    int sum =0;
    for(int i: vecIn){
        sum += i;
    }
    return sum;
}

void PrintStrings(std::string s1In, std::string s2In){
    std::cout << s1In + s2In <<"\n";
}

int main() 
{
    auto d = 3;
    auto f = 7;
    std::cout << AdditionFunction(d, f) << "\n";

    std::vector<int> v {1, 2, 3};
    std::cout << vectorAddition(v) << "\n";

    std::string s1 = "C++ is ";
    std::string s2 = "super awesome.";
    
    // Uncomment the following line to call your function:
    PrintStrings(s1, s2);
}