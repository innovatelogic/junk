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

// cl /EHsc mycode.cpp



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
/*std::istream& operator>>(std::istream &stream, Date &d)
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
}*/

class Database 
{
public:
    void AddEvent(const Date& date, const std::string &event)
    {
         m_events[date].insert(event);
    }

    bool DeleteEvent(const Date& date, const std::string& event)
    {
        bool res = false;

        if (m_events.count(date) >= 1)
        {
            if (m_events[date].count(event))
            {
                m_events[date].erase(event);
                res = true;
            }
        }
        return res;
    }

    int DeleteDate(const Date& date)
    {
        int out = 0;

        if (m_events.count(date) >= 1)
        {
            out = m_events[date].size();
            m_events.erase(date);
        }
        return out;
    }

    std::set<std::string> Find(const Date& date) const
    {
        if (m_events.count(date) >= 1)
        {
            return m_events.at(date);
        }
        return {};
    }

    void Print() const
    {
        for (const auto &i : m_events)
        {
            for (const auto &e : i.second)
            {
                std::cout << i.first << ' ' << e << std::endl;
            }
        }
    }

private:
    std::map<Date, std::set<std::string>> m_events;
};

Date read_date(std::stringstream &ss, std::string &s_date)
{
    Date date;

    //std::stringstream ss_date(s_date);

    try {
        date = parseDate(s_date);
    }
    catch (const std::invalid_argument& e) {

       /* std::string exp = e.what();
        if (exp == "Wrong date format:") {
            throw std::invalid_argument(std::string(e.what()) + ' ' + s_date);
        }*/
        throw;
    }

    return date;
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
}