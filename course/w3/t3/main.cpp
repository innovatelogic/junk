#include "bus_manager.h"

// cl /EHsc mycode.cpp


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