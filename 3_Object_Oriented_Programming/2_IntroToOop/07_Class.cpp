#include <iostream>
#include <cassert>

class Date{
    private:
        int day_{1};
        int month_{1};
        int year_{0};
    public:
        void Day(int d){if(d>1 && d<31) day_ = d;};
        int Day(){return day_;};
    
        void Month(int m){if(m>1 && m<12) month_=m;};
        int Month(){return month_;}
    
        void Year(int y){//year can be anything so 
                            year_=y;}
        int Year(){return year_;};
};

// Test in main
int main()
{
    Date date;
    date.Day(-1);
    date.Month(14);
    date.Year(2000);
    assert(date.Day() != -1);
    assert(date.Month() != 14);
    assert(date.Year() == 2000);
    std::cout << date.Day() << "/" << date.Month() << "/" << date.Year() << std::endl;
}

