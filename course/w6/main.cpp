#include "database.h"
#include "condition_parser.h"

#include <iostream>
#include <stdexcept>

using namespace std;

// cl /EHsc main.cpp database.cpp date.cpp condition_parser.cpp token.cpp node.cpp -o out/course

string trim(string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

//----------------------------------------------------------------------------------------------
std::string ParseEvent(istream& is)
{
    std::string event(std::istreambuf_iterator<char>(is), {});
    return trim(event);
}

void TestAll();

//----------------------------------------------------------------------------------------------
int main() 
{
    //TestAll();

    Database db;

    for (std::string line; getline(cin, line); ) 
    {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "Add") 
        {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);

            db.Add(date, event);
        } 
        else if (command == "Print")
        {
            db.Print(cout);
        } 
        else if (command == "Del") 
        {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };
            int count = db.RemoveIf(predicate);
            cout << "Removed " << count << " entries" << endl;
        } 
        else if (command == "Find")
        {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const std::string& event) {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            for (const auto& entry : entries) {
                std::cout << entry << std::endl;
            }
            std::cout << "Found " << entries.size() << " entries" << std::endl;
        } 
        else if (command == "Last") 
        {
            try {
                cout << db.Last(ParseDate(is)) << endl;
            } catch (invalid_argument&) {
                cout << "No entries" << endl;
            }
        } 
        else if (command.empty()) {
            continue;
        } 
        else
        {
            throw logic_error("Unknown command: " + command);
        }
  }

  return 0;
}
/*
void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }
  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
  }
  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
  }
}

void TestAll() {
  TestRunner tr;
  tr.RunTest(TestParseEvent, "TestParseEvent");
  tr.RunTest(TestParseCondition, "TestParseCondition");
}*/