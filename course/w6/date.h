#pragma once

#include <sstream>
#include <istream>

class Date
{
public:
    Date();
    Date(int year, int month, int day);
    
    int GetYear() const { return year; }
    int GetMonth() const { return month; }
    int GetDay() const { return day; }

    int year = 0;
    int month = 0;
    int day = 0;
};

std::ostream& operator<<(std::ostream &stream, const Date &d);

bool operator<(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);

Date ParseDate(std::istream& is);