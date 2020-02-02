#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <map>

// cl /EHsc mycode.cpp

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

struct BusesForStopResponse
{
    t_order_busstops t_ordered;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r)
{
    if (r.t_ordered.empty())
    {
        std::cout << "No stop" << std::endl;
    }
    else
    {
        for (const auto &i : r.t_ordered)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    return os;
}

struct StopsForBusResponse 
{
    std::vector<std::pair<std::string, std::vector<std::string>>> stop_table;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) 
{
    if (r.stop_table.empty())
    {
        os << "No bus" << std::endl;
    }
    else
    {
        for (const auto &it : r.stop_table)
        {
            os << "Stop " << it.first << ": ";

            if (it.second.empty())
            {
                os << "no interchange";
            }
            else
            {
                for (const auto &it_bus : it.second)
                {
                    os << it_bus << " ";
                }
            }
            os << std::endl;
        }
    }

    return os;
}

struct AllBusesResponse 
{
    t_busstops busstops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) 
{
    if (r.busstops.empty())
    {
        os << "No buses" << std::endl;
    }
    else
    {
        for (auto iter : r.busstops)
        {
            os << "Bus " << iter.first << ": ";

            for (const auto &it_bus : iter.second)
            {
                os << it_bus << " ";
            }

            os << std::endl;
        }
    }
    return os;
}

class BusManager
{
public:
    void AddBus(const string& bus, const vector<string>& stops) 
    {
        const size_t stop_count = stops.size();

        busstops[bus] = stops;
        t_ordered.push_back(bus);
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const 
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

    StopsForBusResponse GetStopsForBus(const string& bus) const 
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

    AllBusesResponse GetAllBuses() const 
    {
       return {busstops};
    }

    t_busstops busstops;
    t_order_busstops t_ordered;
};

// ÐÐµ Ð¼ÐµÐ½ÑÑ Ñ‚ÐµÐ»Ð° Ñ„ÑƒÐ½ÐºÑ†Ð¸Ð¸ main, Ñ€ÐµÐ°Ð»Ð¸Ð·ÑƒÐ¹Ñ‚Ðµ Ñ„ÑƒÐ½ÐºÑ†Ð¸Ð¸ Ð¸ ÐºÐ»Ð°ÑÑÑ‹ Ð²Ñ‹ÑˆÐµ

int main() 
{
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) 
  {
    cin >> q;
    switch (q.type) 
    {
    case QueryType::NewBus:
        bm.AddBus(q.bus, q.stops);
        break;
    case QueryType::BusesForStop:
        cout << bm.GetBusesForStop(q.stop) << endl;
        break;
    case QueryType::StopsForBus:
        cout << bm.GetStopsForBus(q.bus) << endl;
        break;
    case QueryType::AllBuses:
        cout << bm.GetAllBuses() << endl;
        break;
    }
  }

  return 0;
}