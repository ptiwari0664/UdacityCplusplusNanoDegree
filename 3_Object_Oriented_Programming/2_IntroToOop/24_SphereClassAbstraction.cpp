#include <cassert>
#include <cmath>
#include <stdexcept>
#include <iostream>

// TODO: Define class Sphere
class Sphere {
    private:
        // Private members
        int _radius;
        float _volume;
        void Validate(){
            if(_radius  < 0)
                throw std::invalid_argument("Negative Dimension Inserted");
        };

    public:
        // Constructor
        Sphere(int rad):_radius(rad),_volume(std::pow(rad,3) * M_PI * (4.0/3.0)){Validate();};
        // Accessors
        void Radius(const int rad);
        int Radius() const {return this->_radius;}
        float Volume();

};

//Mutators
void Sphere::Radius(const int rad){
    if(rad >0){
        this->_radius = rad;
        this->_volume = this->Volume();
    }
    else
        throw std::invalid_argument("Radius can not be negative");
    
}

float Sphere::Volume(){
    this->_volume = std::pow(this->_radius,3) * M_PI * (4.0/3.0);
    return (this->_volume);
}

// Test
int main(void) {
    Sphere sphere(5);
    assert(sphere.Radius() == 5);
    assert(abs(sphere.Volume() - 523.6) < 1);
}