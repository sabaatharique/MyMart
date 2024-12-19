#include "Date.h"

Date::Date() {}

Date::~Date() {}

int Date::GetDay() const
{
    return day;
}

Months Date::GetMonth() const
{
    return month;
}

int Date::GetYear() const
{
    return year;
}

void Date::GetTodaysDate()
{
    time_t now = time(0);
    tm *today = localtime(&now);

    this->day = today->tm_mday;
    this->month = static_cast<Months>(today->tm_mon);
    this->year = today->tm_year - 100;
}

string Date::ToString()
{
    string res = "";

    if(day < 10) res += '0';
    res += to_string(day) + '-';
    int numericMonth = static_cast<int>(month) + 1;
    if(numericMonth < 10) res += '0';
    res += to_string(numericMonth) + '-';
    if(year < 10) res += '0';
    res += to_string(year);

    return res;
}

void Date::ToDate(const char* date)
{
    day = (date[0] - '0')*10 + (date[1] - '0');
    month = static_cast<Months>((date[3] - '0')*10 + (date[4] - '0') - 1);
    year = (date[6] - '0')*10 + (date[7] - '0');
}
