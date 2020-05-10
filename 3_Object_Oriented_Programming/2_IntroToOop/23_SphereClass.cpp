#include <cassert>
#include <cmath>
#include <stdexcept>
#include <iostream>

// TODO: Define class Sphere
class Sphere {
    private:
        // Private members
        int _radius;
        void Validate(){
            if(_radius  < 0)
                throw std::invalid_argument("Negative Dimension Inserted");
        };

    public:
        // Constructor
        Sphere(int rad):_radius(rad){Validate();};
        // Accessors
        void Radius(const int rad);
        int Radius() const {return this->_radius;}
        float Volume();

};


void Sphere::Radius(const int rad){
    this->_radius = rad;
}

float Sphere::Volume(){
    return (std::pow(this->_radius,3) * M_PI * (4.0/3.0));
}

// Test
int main(void) {
    Sphere sphere(5);
    assert(sphere.Radius() == 5);
    assert(abs(sphere.Volume() - 523.6) < 1);
}