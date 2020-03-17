#include "database.h"

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <iomanip>
#include <istream>
#include <algorithm>
#include <cctype>
#include <utility>

// cl /EHsc mycode.cpp

//----------------------------------------------------------------------------------------------
void Database::Add(const Date &date, const std::string &event)
{
    auto iter_find = m_events.find(date);

    if (iter_find == m_events.end())
    {
        std::pair<std::set<std::string>, std::vector<std::string>> p;
        p.first.insert(event);
        p.second.push_back(event);
        m_events[date] = p;
    }
    else
    {
        std::pair<std::set<std::string>, std::vector<std::string>> &ref_pair = iter_find->second;
        if (ref_pair.first.count(event) == 0)
        {
            ref_pair.first.insert(event);
            ref_pair.second.push_back(event);
        }
    }
}

//----------------------------------------------------------------------------------------------
std::deque<std::string> Database::FindIf(std::function<bool(Date, string)> predicate) const
{
    std::deque<std::string> out;

    for (const auto &i : m_events)
    {
        for (const auto &e : i.second.second)
        {
            if (predicate(i.first, e))
            {
                std::ostringstream ss;

                ss << i.first << " " << e;
                out.push_back(ss.str());
            }
        }
    }

    return out;
}

//----------------------------------------------------------------------------------------------
int Database::RemoveIf(std::function<bool(Date, string)> predicate)
{
    int counter = 0;

    for (auto it = m_events.begin(); it != m_events.end();)
    {
       // if (predicate(it->first, ""))

        //std::cout << "[0]" << std::endl;
        auto last = std::stable_partition(it->second.second.begin(), it->second.second.end(),
                        [&](const std::string &ev)
                        {
                            return !predicate(it->first, ev);
                        });

        //for (auto i = it->second.second.begin(); i != it->second.second.end(); ++i){
        //    std::cout << *i << ' ';
        //}
        //std::cout << std::endl;

        for (auto i = last; i != it->second.second.end(); ++i){
            it->second.first.erase(*i);
            ++counter;
        }

        it->second.second.erase(last, it->second.second.end());

        //for (auto i = it->second.second.begin(); i != it->second.second.end(); ++i){
        //    std::cout << *i << ' ';
        // }
        //std::cout << std::endl;

        if (it->second.second.empty()){
            m_events.erase(it++);
        }
        else
        {
            ++it;
        }
       
    }

    return counter;
}

//----------------------------------------------------------------------------------------------
void Database::Print(std::ostream& ss) const
{
    for (const auto &i : m_events)
    {
        for (const auto &e : i.second.second)
        {
            ss << i.first << ' ' << e << std::endl;
        }
    }
}

//----------------------------------------------------------------------------------------------
std::string Database::Last(const Date &date) const
{
    std::string out;

    if (m_events.empty()){
        return "No entries";
    }

    auto iter_find = m_events.upper_bound(date);

    if (iter_find == m_events.begin()){
        return "No entries";
    }

    --iter_find;

    std::ostringstream ss;

    ss << iter_find->first << " " << *(iter_find->second.second.rbegin());
 
    return ss.str();
}

//----------------------------------------------------------------------------------------------
#if 0

void check_date_input_div(std::istream &stream)
{
    char c;
    stream >> c;

    if (c != '-') {
        throw std::invalid_argument("Wrong date format:");
    }
}

bool is_starts_with_minus(const std::string& s)
{
    return s[0] == '-';
}

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !(std::isdigit(c)); }) == s.end();
}

/*
Date parseDate(std::string &date)
{
    std::istringstream date_stream(date);
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
    flag = flag && date_stream.eof();

    if (!flag)
    {
        throw std::invalid_argument("Wrong date format: " + date);
    }

    return Date(year, month, day);
}
std::istream& operator>>(std::istream &stream, Date &d)
{
    int year;
    int month;
    int day;

    if (stream.peek() == EOF){
        throw std::invalid_argument("Wrong date format:");
    }
    stream >> year;

    check_date_input_div(stream);

    char c = stream.peek();

    //std::cout << "peek: " << c << std::endl;

    bool b_plus = c == '+';
    bool b_minus =  c == '-';

    stream >> month;

    if (stream.peek() == EOF){
        throw std::invalid_argument("Wrong date format:");
    }

    if (month <= 0 || month > 12){

        std::string err = std::to_string(month);

        if (b_plus){
            err = std::string("+") + err;
        }

        if (b_minus){
            err = std::string("-") + err;
        }

        throw std::invalid_argument("Month value is invalid: " + err);
    }

    check_date_input_div(stream);

    std::string s_day;
    std::getline(stream, s_day);

    b_plus = false;
    if (s_day[0] == '+')
    {
        s_day = s_day.substr(1);
        b_plus = true;
    }

    b_minus = false;
    if (s_day[0] == '-')
    {
        s_day = s_day.substr(1);
        b_minus = true;
    }

    if (!is_number(s_day)){
        throw std::invalid_argument("Wrong date format:");
    }
    //stream >> day;
    day = std::atoi(s_day.c_str()) * (b_minus ? -1 : 1);

    //std::cout << day << std::endl;

    if (day <= 0 || day > 31){

        std::string err = std::to_string(day);

        if (b_plus){
            err = std::string("+") + err;
        }

        if (b_minus){
            err = std::string("-") + err;
        }

        throw std::invalid_argument("Day value is invalid: " + err);
    }

    if (stream.peek() != EOF){
        throw std::invalid_argument("Wrong date format:");
    }

    d.year = year;
    d.month = month;
    d.day = day;

    //std::cout << year << " " << month << " " << day << std::endl;

    return stream;
}

int main()
{
    Database db;
    
    std::string command;
    while (getline(std::cin, command))
    {
        if (command.empty()){
            continue;
        }

        try
        {
            std::stringstream ss(command);

            std::string s_cmd;
            std::string s_date;
            std::string s_event;

            ss >> s_cmd;
            
            if (s_cmd == "Add")
            {
                ss >> s_date;

                Date date = read_date(ss, s_date);

                ss >> s_event;

                if (!s_event.empty())
                {
                    db.AddEvent(date, s_event);
                }
            }
            else if (s_cmd == "Del")
            {
                ss >> s_date;

                Date date = read_date(ss, s_date);

                ss >> s_event;

                if (s_event.empty())
                {
                    int size = db.DeleteDate(date);

                    std::cout << "Deleted " << std::to_string(size) << " events" << std::endl;
                }
                else
                {
                    if (db.DeleteEvent(date, s_event))
                    {
                        std::cout << "Deleted successfully" << std::endl;
                    }
                    else
                    {
                        std::cout << "Event not found" << std::endl;
                    }
                }
            }
            else if (s_cmd == "Find")
            {
                ss >> s_date;
                
                Date date = read_date(ss, s_date);

                std::set<std::string> events = db.Find(date);

                for (const auto &e : events)
                {
                    std::cout << e << std::endl;
                }
            }
            else if (s_cmd == "Print")
            {
                db.Print();
            }
            else {
                std::cout << "Unknown command: " << s_cmd << std::endl;
            }
        }
        catch(std::invalid_argument& e)
        {
            std::cout << e.what() << '\n';
        }
    }

    return 0;
}*/

#endif