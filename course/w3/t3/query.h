#pragma once

#include <string>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

using t_busstops = std::map<std::string, std::vector<std::string>>;
using t_order_busstops = std::vector<std::string>;

istream& operator >> (istream& is, Query& q);