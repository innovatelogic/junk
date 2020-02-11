#include "bus_manager.h"
#include <algorithm>

void BusManager::AddBus(const string& bus, const vector<string>& stops) 
{
    const size_t stop_count = stops.size();

    busstops[bus] = stops;
    t_ordered.push_back(bus);
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const 
{
    std::vector<std::string> res;

    for (const auto &iter : t_ordered)
    {
        const auto iter_find = std::find(begin(busstops.at(iter)), end(busstops.at(iter)), stop);
        if (iter_find != busstops.at(iter).end())
        {
            res.push_back(iter);
        }
    }
    return {res};
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const 
{
    std::vector<std::pair<std::string, std::vector<std::string>>> stop_table;

    if (busstops.count(bus) == 0){
        return {};
    }

    for (const auto &stop : busstops.at(bus))
    {
        stop_table.push_back(std::make_pair(stop, std::vector<std::string>()));

        for (const auto &bus2 : t_ordered)
        {
            if (bus2 != bus)
            {
                if (std::find(begin(busstops.at(bus2)), end(busstops.at(bus2)), stop) != busstops.at(bus2).end())
                {
                    stop_table[stop_table.size() - 1].second.push_back(bus2);
                }
            }
        }
    }

    return {stop_table};
}

AllBusesResponse BusManager::GetAllBuses() const 
{
    return {busstops};
}