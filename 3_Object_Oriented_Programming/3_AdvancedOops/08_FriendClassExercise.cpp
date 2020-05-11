// Example solution for Rectangle and Square friend classes
#include <iostream>
#include <string>
#include <cassert>

class Square{
    private:
        // Add private attribute side
        // Add friend class Rectangle
        int side_;
        friend class Rectangle;
    public:
        // Add public constructor to Square, initialize side
        Square(int s) : side_(s){}
};

// Declare class Rectangle
class Rectangle{
    // Add private attributes width, height;
    // Define class Square as friend of Rectangle
    private:
        int width_;
        int height_;
    
    // Add public function to Rectangle: Area()
    public:
    // Define a Rectangle constructor that takes a Square
        Rectangle(const Square& s): width_(s.side_), height_(s.side_){}
        int Area(){return this->width_ * this->height_;}
};

// Update main() to pass the tests
int main()
{
    Square square(4);
    Rectangle rectangle(square);
    assert(rectangle.Area() == 16); 
}