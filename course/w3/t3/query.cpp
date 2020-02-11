#include "query.h"
#include <iostream>

istream& operator >> (istream& is, Query& q) 
{
    std::string op;

    is >> op;

    if (op == "NEW_BUS")
    {
        q.type = QueryType::NewBus;

        std::string n;
        int stop_count;
        cin >> q.bus >> stop_count;

        q.stops.resize(stop_count);

        int i = 0;
        while (stop_count)
        {
            cin >> q.stops[i];

            ++i;
            --stop_count;
        }
    }
    else if (op == "BUSES_FOR_STOP")
    {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }
    else if (op == "STOPS_FOR_BUS")
    {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }
    else if (op == "ALL_BUSES")
    {
        q.type = QueryType::AllBuses;
    }

    return is;
}