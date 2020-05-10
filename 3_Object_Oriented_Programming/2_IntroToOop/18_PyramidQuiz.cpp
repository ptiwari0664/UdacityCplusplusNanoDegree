#include <cassert>
#include <stdexcept>

// TODO: Define class Pyramid
class Pyramid{

// public class members
private:
    int _length;
    int _width;
    int _height;
    void Validate(){
        if(_length <=0 || _width<=0 || _height <=0)
            throw std::invalid_argument("Negative Dimension Inserted");
    };

public:
    //Initiated Constructor with initial values to private members
    Pyramid(int len, int wid, int hei):_length(len),_width(wid),_height(hei){Validate();};

    //Accessors
    //Function Overloading
    int Length() const {return this->_length;};
    int Width() const {return this->_width;};
    int Height() const {return this->_height;}

    //Mutators
    void Length(const int l);
    void Width(const int w);
    void Height(const int h);
    float Volume() const;
};

void Pyramid::Length(const int l){
        this->_length = l;
}

void Pyramid::Width(const int w){
        this->_width = w;
}

void Pyramid::Height(const int h){
        this->_height = h;
}

// mutators
// public Volume() function
float Pyramid::Volume() const {
    return (this->_length * this->_width * (this->_height/3));
}


// Test
int main() {
    Pyramid pyramid(4, 5, 6);
    assert(pyramid.Length() == 4);
    assert(pyramid.Width() == 5);
    assert(pyramid.Height() == 6);
    assert(pyramid.Volume() == 40);

    bool caught{false};
    try {
        Pyramid invalid(-1, 2, 3);
    } catch (...) {
        caught = true;
    }
    assert(caught);
}