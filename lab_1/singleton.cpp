#include <iostream>
using namespace std;

class Singleton {
   private:
    int year, month, day;

   public:
    Singleton() {
        year = 2000;
        month = 12;
        day = 30;
        get();
    }

    Singleton(int date_year, int date_month, int date_day) {
        year = date_year;
        month = date_month;
        day = date_day;
        get();
    }

    void message() { cout << "Hello world, i'm working!" << endl; }
    void set(int date_year, int date_month, int date_day) {
        year = date_year;
        month = date_month;
        day = date_day;
    }
    void get() { cout << "Year: " << year << " Month: " << month << " Day: " << day << endl; }

//    ~Singleton() { cout << "Class is not working" << endl; }
};

int main() {
    Singleton single(2005, 11, 17);

    return 0;
}