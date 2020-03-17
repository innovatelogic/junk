#include "airline_ticket.h"
#include "test_runner.h"
#include <sstream>
#include <iostream>

using namespace std;

#define UPDATE_FIELD(ticket, field, values) {\
    map<string, string>::const_iterator it_find = values.find(#field);\
    if (it_find != values.end())\
    {\
        std::stringstream ss(it_find->second);\
        ss >> ticket.field;\
    }\
}

//----------------------------------------------------------------------------------------------
bool operator< (const Date &lhs, const Date &rhs)
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
bool operator== (const Date &lhs, const Date &rhs)
{
    return lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day;
}

//----------------------------------------------------------------------------------------------
bool operator<(const Time &lhs, const Time &rhs)
{
    if (lhs.hours == rhs.hours)
    {
        return lhs.minutes < rhs.minutes;
    }
    return lhs.hours < rhs.hours;
}

//----------------------------------------------------------------------------------------------
bool operator==(const Time &lhs, const Time &rhs)
{
    return lhs.hours == rhs.hours && lhs.minutes == rhs.minutes;
}

//----------------------------------------------------------------------------------------------
ostream& operator<<(ostream& stream, const Date &date)
{
    stream << date.day << " " << date.month << " " << date.year;
    return stream;      
}

//----------------------------------------------------------------------------------------------
ostream& operator<<(ostream& stream, const Time &date)
{
    stream << date.minutes << " " << date.hours;
    return stream;      
}

//----------------------------------------------------------------------------------------------
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

    if (!flag) {
        throw std::invalid_argument("Wrong date format: " + date);
    }

    return {year, month, day};
}

//----------------------------------------------------------------------------------------------
Time parseTime(std::string &time)
{
    std::istringstream date_stream(time);
    bool flag = true;

    int hours;
    flag = flag && (date_stream >> hours);
    flag = flag && (date_stream.peek() == ':');
    date_stream.ignore(1);

    int minutes;
    flag = flag && (date_stream >> minutes);
    flag = flag && date_stream.eof();

    if (!flag) {
        throw std::invalid_argument("Wrong date format: " + time);
    }

    return {hours, minutes};
}

//----------------------------------------------------------------------------------------------
Date read_date(std::stringstream &ss, std::string &s_date)
{
    Date date;

    try {
        date = parseDate(s_date);
    }
    catch (const std::invalid_argument& e) {
        throw;
    }

    return date;
}

//----------------------------------------------------------------------------------------------
std::stringstream& operator>>(std::stringstream &ss, Date &d)
{
    std::string str_date;
    ss >> str_date;
    d = parseDate(str_date);
    return ss;
}

//----------------------------------------------------------------------------------------------
std::stringstream& operator>>(std::stringstream &ss, Time &d)
{
    std::string str_time;
    ss >> str_time;
    d = parseTime(str_time);
    return ss;
}


//----------------------------------------------------------------------------------------------
void TestUpdate()
 {

 std::cout << "Start" << std::endl;
  AirlineTicket t;
  t.price = 0;

  const map<string, string> updates1 = {
    {"departure_date", "2018-2-28"},
    {"departure_time", "17:40"},
  };


  UPDATE_FIELD(t, departure_date, updates1);

  UPDATE_FIELD(t, departure_time, updates1);

  UPDATE_FIELD(t, price, updates1);


  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 0);

  const map<string, string> updates2 = {
    {"price", "12550"},
    {"arrival_time", "20:33"},
  };
  UPDATE_FIELD(t, departure_date, updates2);
  UPDATE_FIELD(t, departure_time, updates2);
  UPDATE_FIELD(t, arrival_time, updates2);
  UPDATE_FIELD(t, price, updates2);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() 
{
    TestRunner tr;
    RUN_TEST(tr, TestUpdate);
    return 0;
}

/*
#include "airline_ticket.h"
#include <tuple>
#include <iostream>
using namespace std;

bool operator == (const Date& lhs, const Date& rhs) {
  return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}

bool operator == (const Time& lhs, const Time& rhs) {
  return tie(lhs.hours, lhs.minutes) == tie(rhs.hours, rhs.minutes);
}

istream& operator>>(istream& is, Date& d) {
  is >> d.year;
  is.ignore(1);
  is >> d.month;
  is.ignore(1);
  is >> d.day;
  return is;
}

ostream& operator<<(ostream& os, const Date& d) {
  return os << d.year << '-' << d.month << '-' << d.day;
}

istream& operator>>(istream& is, Time& t) {
  is >> t.hours;
  is.ignore(1);
  is >> t.minutes;
  return is;
}

ostream& operator<<(ostream& os, const Time& t) {
  return os << t.hours << ':' << t.minutes;
}

#define UPDATE_FIELD(ticket, field, values) \
  {                                         \
    auto it = values.find(#field);          \
    if (it != values.end()) {               \
      istringstream is(it->second);         \
      is >> ticket.field;                   \
    }                                       \
  }
*/