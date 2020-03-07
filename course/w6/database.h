#pragma once

#include "date.h"

#include <string>
#include <map>
#include <set>
#include <iostream>

class Database 
{
public:
    void Add(const Date& date, const std::string &event);

    bool DeleteEvent(const Date& date, const std::string& event);

    int DeleteDate(const Date& date);

    std::set<std::string> Find(const Date& date) const;

    void Print(std::ostream& stream) const;

private:
    std::map<Date, std::set<std::string>> m_events;
};
