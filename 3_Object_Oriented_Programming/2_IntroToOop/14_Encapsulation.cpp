#include <cassert>

class Date {
public:
    Date(int day, int month, int year);
    int Day() const { return day_; }
    void Day(int day);
    int Month() const { return month_; }
    void Month(int month);
    int Year() const { return year_; }
    void Year(int year);

private:
    int day_{1};
    int month_{1};
    int year_{0};
    int monthDays(const int m, const int y);
};

Date::Date(int day, int month, int year) {
  Year(year);
  Month(month);
  Day(day);
}

int Date::monthDays(const int m, const int y){
    int no_of_days = 0;

    if(m%2 == 0 && m!=8)
    {
        no_of_days = 30;
        if(y%4 == 0 && m==2)
            no_of_days = 29;
        else if(y%4 != 0 && m ==2)
            no_of_days = 28;
    }
    else{
        no_of_days = 31;
    }


    if(y%4 == 0){
        if(m == 2)
            no_of_days = 29;
        else if( m%2 == 0){
            no_of_days
        }
    }
}

void Date::Day(int day) {
  if (day >= 1 && day <= 31)
    day_ = day;
}

void Date::Month(int month) {
  if (month >= 1 && month <= 12)
    month_ = month;
}

void Date::Year(int year) { year_ = year; }

// Test
int main() {
  Date date(29, 8, 1981);
  assert(date.Day() == 29);
  assert(date.Month() == 8);
  assert(date.Year() == 1981);
}