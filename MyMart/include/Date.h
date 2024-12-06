#ifndef DATE_H
#define DATE_H

#include<iostream>

using namespace std;

enum Months {
    january,
    february,
    march,
    april,
    may,
    june,
    july,
    august,
    september,
    october,
    november,
    december
};

class Date
{
    public:
        Date();
        ~Date();

        int GetDay() const;
        Months GetMonth() const;
        int GetYear() const;

        string ToString();

        void ToDate(const char* date);

    protected:

    private:
        int day;
        Months month;
        int year;
};

#endif // DATE_H
