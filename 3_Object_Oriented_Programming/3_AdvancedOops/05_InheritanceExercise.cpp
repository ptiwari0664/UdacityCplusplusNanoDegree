#include <iostream>
#include <string>
#include <cassert>


// Define base class Animal
class Animal{
    private:
        std::string color_;
        std::string name_;
        int age_;
    public:
        void Color(std::string c){this->color_ = c;};
        void Name(std::string n){this->name_ =n;}
        void Age(int a){this->age_ = a;}

        std::string Color() const {return this->color_;}
        std::string Name() const {return this->name_;}
        int Age() const {return this->age_;}
};

// Declare derived class Snake
class Snake: public Animal {
    private: 
        int length_;
    public:
        Snake(int l,std::string c, std::string n,int a):length_(l){
            Color(c);
            Name(n);
            Age(a);
        }
        void MakeSound(){ std::cout << "Ssssssss \n";}
        void Length(const int l){ if(l>0) this->length_ =l;}
        int Length() const {return this->length_;}

};

// Declare derived class Cat
class Cat: public Animal{
    private:
        int height_;
    public:
        Cat(int h,std::string c, std::string n,int a):height_(h){
            Color(c);
            Name(n);
            Age(a);
        }
        void MakeSound(){std::cout << "Mmmiiiiaaaauuuuu \n";}
        int Height(){return this->height_;};
};

// Test in main()
int main(){

    Snake snake1(10,"Black","Cobra",2);
    snake1.MakeSound();

    Cat cat1(1,"White","Lucy",5);
    cat1.MakeSound();

    assert(snake1.Length() == 10);
    assert(snake1.Color() == "Black");
    assert(snake1.Name() == "Cobra");
    assert(snake1.Age() == 2);

    assert(cat1.Height() == 1);
    assert(cat1.Color() == "White");
    assert(cat1.Name() == "Lucy");
    assert(cat1.Age() == 5);
    return 0;
}