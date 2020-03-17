#pragma once

#include "date.h"

#include <string>
#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <functional>
#include <deque>

using namespace std;

class Database 
{
public:
    void Add(const Date& date, const std::string &event);

    std::deque<std::string> FindIf(std::function<bool(Date, string)>) const;

    int RemoveIf(std::function<bool(Date date, string event)> predicate);

    void Print(std::ostream& stream) const;

    std::string Last(const Date &date) const;

private:
    std::map<Date, std::pair<std::set<std::string>, std::vector<std::string>>> m_events;
};
