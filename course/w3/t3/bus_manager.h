#pragma once

#include "responses.h"

class BusManager
{
public:
    void AddBus(const string& bus, const vector<string>& stops);

    BusesForStopResponse GetBusesForStop(const string& stop) const;

    StopsForBusResponse GetStopsForBus(const string& bus) const;

    AllBusesResponse GetAllBuses() const;

    t_busstops busstops;
    t_order_busstops t_ordered;
};
