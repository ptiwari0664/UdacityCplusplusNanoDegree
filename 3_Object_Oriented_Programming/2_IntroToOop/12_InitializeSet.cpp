#include <assert.h>
#include <string>

// TODO: Define class Person
class Person{
public:
    Person(std::string s);
    std::string name_;

    void setName(std::string str);
    std::string getName();
};

Person::Person(std::string consstrinput):name_(consstrinput){
    //setName(s);
    getName();
}

void Person::setName(std::string s){
    if(!s.empty()){
        name_ = s;
    }
}

std::string Person::getName(){
    return this->name_;
}

// Test
int main() {
    Person alice("Alice");
    Person bob("Bob");
    assert(alice.name_ != bob.name_);
}