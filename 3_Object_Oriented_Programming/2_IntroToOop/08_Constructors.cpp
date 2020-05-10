#include <iostream>
#include <cassert>

class Date{
    private:
        int day_{1};
        int month_{1};
        int year_{0};
    public:
        Date(int d, int m, int y){
        Day(d);
        Month(m);
        Year(y);
        }

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
    Date date(29,8,1981);
    assert(date.Day() == 29);
    assert(date.Month() == 8);
    assert(date.Year() == 1981);
    std::cout << date.Day() << "/" << date.Month() << "/" << date.Year() << std::endl;
}

