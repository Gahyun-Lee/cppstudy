#include <iostream>

class Date {
    int year_;
    int month_;
    int day_;
    
public:
    void SetDate(int year, int month, int day) {
        year_ = year;
        month_ = month;
        day_ = day;
    }
    void AddDay(int inc) {
        day_ += inc;
        int day[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        while(1){
            if(month_==2) {
                if(year_%4==0 && year_%100 !=0 && year_%400!=0) {
                    day[month_] = 29;
                }
                else
                    day[month_] = 28;
            }
            if(day_ <= day[month_])
                break;
            else {
                day_ -= day[month_];
                AddMonth(1);
            }
        }
    }
    void AddMonth(int inc) {
        month_ += inc;
        if(month_ > 12) {
            int inc = month_/12;
            month_ -= 12*inc;
            AddYear(inc);
        }
    }
    void AddYear(int inc) {
        year_ += inc;
    }
    void ShowDate() {
        std::cout<<year_<<"년 "<<month_<<"월 "<<day_<<"일"<<std::endl;
    }
};

int main() {
    Date date;
    date.SetDate(2023, 11, 25);
    date.ShowDate();
    date.AddDay(5111);
    date.ShowDate();
}
