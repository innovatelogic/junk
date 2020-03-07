#include "date.h"

#include <iostream>
#include <stdexcept>
#include <iomanip>

//----------------------------------------------------------------------------------------------
Date::Date()
: year(0)
, month(0)
, day(0)
{}

//----------------------------------------------------------------------------------------------
Date::Date(int year, int month, int day)
: year(year)
, month(month)
, day(day)
{
    if (month <= 0 || month > 12)
    {
        throw std::invalid_argument("Month value is invalid: " + std::to_string(month));
    }
    if (day <= 0 || day > 31){
        throw std::invalid_argument("Day value is invalid: " + std::to_string(day));
    }
}

//----------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream &stream, const Date &d)
{
    stream << std::setfill('0');
    stream << std::setw(4) << d.year;
    stream << '-';
    stream << std::setw(2) << d.month;
    stream << '-';
    stream << std::setw(2) << d.day;

    return stream;
}

//----------------------------------------------------------------------------------------------
bool operator<(const Date& lhs, const Date& rhs)
{
    if (lhs.year == rhs.year)
    {
        if (lhs.month == rhs.month)
        {
            return lhs.day < rhs.day;
        }
        return lhs.month < rhs.month;
    }
    return lhs.year < rhs.year;
}

//----------------------------------------------------------------------------------------------
bool operator==(const Date& lhs, const Date& rhs)
{
    return lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day;
}

//----------------------------------------------------------------------------------------------
Date ParseDate(std::istream& date_stream)
{
    bool flag = true;

    int year;
    flag = flag && (date_stream >> year);
    flag = flag && (date_stream.peek() == '-');
    date_stream.ignore(1);

    int month;
    flag = flag && (date_stream >> month);
    flag = flag && (date_stream.peek() == '-');
    date_stream.ignore(1);

    int day;
    flag = flag && (date_stream >> day);
    //flag = flag && date_stream.eof();

    if (!flag)
    {
        throw std::invalid_argument("Wrong date format");
    }

    return Date(year, month, day);
}

//----------------------------------------------------------------------------------------------
#if 0

void TestDate()
{
    std::string line;
    getline(std::cin, line);

    std::istringstream is(line);

    std::cout << ParseDate(is) << std::endl;
}

//----------------------------------------------------------------------------------------------
int main()
{
    TestDate();
    return 0;
}

#endif