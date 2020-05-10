#include <iostream>
#include <cassert>

class Date{
    private:
        int day_{1};
        int month_{1};
        int year_{0};
    public:
        Date(int d, int m, int y);

        void Day(const int d);
        int Day() const {return this->day_;};
    
        void Month(const int m);
        int Month() const {return this->month_;}
    
        void Year(const int y);
        int Year() const {return this->year_;};
};

Date::Date(int d, int m, int y){
        Day(d);
        Month(m);
        Year(y);
}

void Date::Day(const int d){
    if(d >=1 && d <= 31)
        this->day_ = d;
};

void Date::Month(const int m){
    if(m >= 1 && m <= 12) 
        this->month_ = m;
};

void Date::Year(const int y){
    this->year_ = y;
}
// Test in main
int main()
{
    Date date(29,8,1981);
    assert(date.Day() == 29);
    assert(date.Month() == 8);
    assert(date.Year() == 1981);
    std::cout << date.Day() << "/" << date.Month() << "/" << date.Year() << std::endl;
}

