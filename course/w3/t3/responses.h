#pragma once

#include "query.h"
#include <string>
#include <iostream>

using namespace std;

struct BusesForStopResponse
{
    t_order_busstops t_ordered;
};

struct StopsForBusResponse 
{
    std::vector<std::pair<std::string, std::vector<std::string>>> stop_table;
};

struct AllBusesResponse 
{
    t_busstops busstops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r);
ostream& operator << (ostream& os, const BusesForStopResponse& r);
ostream& operator << (ostream& os, const AllBusesResponse& r);