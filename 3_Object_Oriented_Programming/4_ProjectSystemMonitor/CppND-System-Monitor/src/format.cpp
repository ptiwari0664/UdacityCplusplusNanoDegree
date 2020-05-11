#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    char timestring[10];
    int nH = seconds / 3600;
    int rest = seconds % 3600;
    int nM = rest / 60;
    int nS = rest % 60;
    sprintf(timestring, "%.2d:%.2d:%.2d", nH, nM, nS);
    
    return timestring;
}