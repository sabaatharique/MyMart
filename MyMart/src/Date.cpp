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
    this->year = today->tm_year + 1900;
}

string Date::ToString()
{
    string res = "";

    res += to_string(year) + '-';

    int numericMonth = static_cast<int>(month) + 1;
    if(numericMonth < 10) res += '0';
    res += to_string(numericMonth) + '-';

    if(day < 10) res += '0';
    res += to_string(day);

    return res;
}

void Date::ToDate(const char* date)
{
    year = (date[0] - '0')*1000 + (date[1] - '0')*100 + (date[2] - '0')*10 + (date[3] - '0');
    month = static_cast<Months>((date[5] - '0')*10 + (date[6] - '0') - 1);
    day = (date[8] - '0')*10 + (date[9] - '0');
}
