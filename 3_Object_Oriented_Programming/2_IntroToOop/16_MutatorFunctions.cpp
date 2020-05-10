#include <string>
#include <cstring>
#include <iostream>

class Car {
    // TODO: Declare private attributes
    private:
        int weight_;
        int horsePower_;
        std::string brand_;
    // TODO: Declare getter and setter for brand
    public:
        Car():weight_(0),horsePower_(0),brand_("na"){};
        
        void setWeight(const int w);
        void setHorsePwr(const int hp);
        void setBrand(char* brandIn);

        int getWeight() const {return this->weight_;};
        int getHorsePwr() const {return this->horsePower_;};
        std::string getBrand() const {return this->brand_;};
};

// Define setters
void Car::setBrand(char* brandIn){
    this->brand_ = brandIn;
}
// Define getters

// Test in main()
int main() 
{
    Car car;
    char carBrand[] = "Peugeot";
    car.setBrand(carBrand);
    std::cout << car.getBrand() << "\n";   
}