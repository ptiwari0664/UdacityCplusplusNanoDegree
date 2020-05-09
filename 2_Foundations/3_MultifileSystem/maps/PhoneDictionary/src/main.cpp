
#include "main.h"

int main() 
{
    int key = 960;
    std::string countryName = "Maldives";
    if(mymap.find(key) == mymap.end()){
        std::cout << "The key is not in the dictionary \n Adding this key to unordered Maps\n\n" ;
        // Set the value for the key.
        mymap[key] = countryName;
    }

    //Now the key is added to the unordered Map
    // Let's Print the key and country
    std::cout << key << ": ";
    auto definitions = mymap[key];
    std::cout << definitions << "\n";
}

