#include <string>
#include <iostream>
#include <cassert>
#include <vector>
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
        in >> q.bus >> stop_count;

        q.stops.resize(stop_count);

        int i = 0;
        while (stop_count)
        {
            in >>q.stops[i];

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
  // ÐÐ°Ð¿Ð¾Ð»Ð½Ð¸Ñ‚Ðµ Ð¿Ð¾Ð»ÑÐ¼Ð¸ ÑÑ‚Ñƒ ÑÑ‚Ñ€ÑƒÐºÑ‚ÑƒÑ€Ñƒ
};

ostream& operator << (ostream& os, const BusesForStopResponse& r)
{
  // Ð ÐµÐ°Ð»Ð¸Ð·ÑƒÐ¹Ñ‚Ðµ ÑÑ‚Ñƒ Ñ„ÑƒÐ½ÐºÑ†Ð¸ÑŽ
  return os;
}

struct StopsForBusResponse 
{
  // ÐÐ°Ð¿Ð¾Ð»Ð½Ð¸Ñ‚Ðµ Ð¿Ð¾Ð»ÑÐ¼Ð¸ ÑÑ‚Ñƒ ÑÑ‚Ñ€ÑƒÐºÑ‚ÑƒÑ€Ñƒ
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) 
{
  // Ð ÐµÐ°Ð»Ð¸Ð·ÑƒÐ¹Ñ‚Ðµ ÑÑ‚Ñƒ Ñ„ÑƒÐ½ÐºÑ†Ð¸ÑŽ
  return os;
}

struct AllBusesResponse 
{
  // ÐÐ°Ð¿Ð¾Ð»Ð½Ð¸Ñ‚Ðµ Ð¿Ð¾Ð»ÑÐ¼Ð¸ ÑÑ‚Ñƒ ÑÑ‚Ñ€ÑƒÐºÑ‚ÑƒÑ€Ñƒ
};

ostream& operator << (ostream& os, const AllBusesResponse& r) 
{
  // Ð ÐµÐ°Ð»Ð¸Ð·ÑƒÐ¹Ñ‚Ðµ ÑÑ‚Ñƒ Ñ„ÑƒÐ½ÐºÑ†Ð¸ÑŽ
  return os;
}

class BusManager
{
public:
    void AddBus(const string& bus, const vector<string>& stops) 
    {
    // Ð ÐµÐ°Ð»Ð¸Ð·ÑƒÐ¹Ñ‚Ðµ ÑÑ‚Ð¾Ñ‚ Ð¼ÐµÑ‚Ð¾Ð´
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const 
    {
    // Ð ÐµÐ°Ð»Ð¸Ð·ÑƒÐ¹Ñ‚Ðµ ÑÑ‚Ð¾Ñ‚ Ð¼ÐµÑ‚Ð¾Ð´
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const 
    {
    // Ð ÐµÐ°Ð»Ð¸Ð·ÑƒÐ¹Ñ‚Ðµ ÑÑ‚Ð¾Ñ‚ Ð¼ÐµÑ‚Ð¾Ð´
    }

    AllBusesResponse GetAllBuses() const 
    {
    // Ð ÐµÐ°Ð»Ð¸Ð·ÑƒÐ¹Ñ‚Ðµ ÑÑ‚Ð¾Ñ‚ Ð¼ÐµÑ‚Ð¾Ð´
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
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
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