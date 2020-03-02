#include "data.h"
#include <stdexcept>

Date::Date()
: year(0)
, month(0)
, day(0)
{}

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