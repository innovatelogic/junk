#pragma once

#include "date.h"

#include <string>
#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <functional>
#include <deque>


class Database 
{
public:
    void Add(const Date& date, const std::string &event);

    bool DeleteEvent(const Date& date, const std::string& event);

    int DeleteDate(const Date& date);

    std::set<std::string> Find(const Date& date) const;

    std::deque<std::string> FindIf(const std::function<bool(const Date& date, const std::string &event)> &predicate);

    void Print(std::ostream& stream) const;

private:
    std::map<Date, std::pair<std::set<std::string>, std::vector<std::string>>> m_events;
};
