#include "test_runner.h"
//#include "profile.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

// TAirport should be enum with sequential items and last item TAirport::Last_
template <typename TAirport>
class AirportCounter {
public:
  // ÐºÐ¾Ð½ÑÑ‚Ñ€ÑƒÐºÑ‚Ð¾Ñ€ Ð¿Ð¾ ÑƒÐ¼Ð¾Ð»Ñ‡Ð°Ð½Ð¸ÑŽ: ÑÐ¿Ð¸ÑÐ¾Ðº ÑÐ»ÐµÐ¼ÐµÐ½Ñ‚Ð¾Ð² Ð¿Ð¾ÐºÐ° Ð¿ÑƒÑÑ‚
  AirportCounter()
  {
    for (size_t i = 0; i < static_cast<uint32_t>(TAirport::Last_); i++)
    {
        m_airports[i].first = static_cast<TAirport>(i);
        m_airports[i].second = 0;
    }
  }

  template <typename TIterator>
  AirportCounter(TIterator begin, TIterator end)
  : AirportCounter()
  {
      for (; begin != end; ++begin)
      {
          size_t i = static_cast<uint32_t>(*begin);
          m_airports[i].second++;
      }
  }

  size_t Get(TAirport airport) const
  {
      return m_airports[static_cast<uint32_t>(airport)].second;
  }

  void Insert(TAirport airport)
  {
    m_airports[static_cast<uint32_t>(airport)].second++;
  }

  void EraseOne(TAirport airport)
  {
    size_t i = static_cast<uint32_t>(airport);
    if (m_airports[i].second > 0){
        m_airports[i].second--;
    }
  }

  void EraseAll(TAirport airport)
  {
      m_airports[static_cast<uint32_t>(airport)].second = 0;
  }

  using Item = pair<TAirport, size_t>;
  using Items = std::array<Item, static_cast<uint32_t>(TAirport::Last_)>;

  const Items& GetItems() const
  {
    return m_airports;
  }

private:
    Items m_airports;
};
/*
void TestMoscow() 
{
  enum class MoscowAirport {
    VKO,
    SVO,
    DME,
    ZIA,
    Last_
  };

  const vector<MoscowAirport> airports = {
      MoscowAirport::SVO, // 1
      MoscowAirport::VKO, // 0
      MoscowAirport::ZIA, // 3
      MoscowAirport::SVO, // 1
  };
  AirportCounter<MoscowAirport> airport_counter(begin(airports), end(airports));

  ASSERT_EQUAL(airport_counter.Get(MoscowAirport::VKO), 1);
  ASSERT_EQUAL(airport_counter.Get(MoscowAirport::SVO), 2);
  ASSERT_EQUAL(airport_counter.Get(MoscowAirport::DME), 0);
  ASSERT_EQUAL(airport_counter.Get(MoscowAirport::ZIA), 1);

  using Item = AirportCounter<MoscowAirport>::Item;
  vector<Item> items;
  for (const auto& item : airport_counter.GetItems()) {
    items.push_back(item);
  }
  ASSERT_EQUAL(items.size(), 4);

#define ASSERT_EQUAL_ITEM(idx, expected_enum, expected_count) \
  do { \
    ASSERT_EQUAL(static_cast<size_t>(items[idx].first), static_cast<size_t>(MoscowAirport::expected_enum)); \
    ASSERT_EQUAL(items[idx].second, expected_count); \
  } while (false)

  ASSERT_EQUAL_ITEM(0, VKO, 1);
  ASSERT_EQUAL_ITEM(1, SVO, 2);
  ASSERT_EQUAL_ITEM(2, DME, 0);
  ASSERT_EQUAL_ITEM(3, ZIA, 1);

  airport_counter.Insert(MoscowAirport::VKO);
  ASSERT_EQUAL(airport_counter.Get(MoscowAirport::VKO), 2);

  airport_counter.EraseOne(MoscowAirport::SVO);
  ASSERT_EQUAL(airport_counter.Get(MoscowAirport::SVO), 1);

  airport_counter.EraseAll(MoscowAirport::VKO);
  ASSERT_EQUAL(airport_counter.Get(MoscowAirport::VKO), 0);
}

enum class SmallCountryAirports {
  Airport_1,
  Airport_2,
  Airport_3,
  Airport_4,
  Airport_5,
  Airport_6,
  Airport_7,
  Airport_8,
  Airport_9,
  Airport_10,
  Airport_11,
  Airport_12,
  Airport_13,
  Airport_14,
  Airport_15,
  Last_
};

void TestManyConstructions() {
  default_random_engine rnd(20180623);
  uniform_int_distribution<size_t> gen_airport(
    0, static_cast<size_t>(SmallCountryAirports::Last_) - 1
  );

  array<SmallCountryAirports, 2> airports;
  for (auto& x : airports) {
    x = static_cast<SmallCountryAirports>(gen_airport(rnd));
  }

  uint64_t total = 0;
  for (int step = 0; step < 100'000'000; ++step) {
    AirportCounter<SmallCountryAirports> counter(begin(airports), end(airports));
    total += counter.Get(SmallCountryAirports::Airport_1);
  }
  // Assert to use variable total so that compiler doesn't optimize it out
  ASSERT(total < 1000);
}

enum class SmallTownAirports {
  Airport_1,
  Airport_2,
  Last_
};

void TestManyGetItems() {
  default_random_engine rnd(20180701);
  uniform_int_distribution<size_t> gen_airport(
    0, static_cast<size_t>(SmallTownAirports::Last_) - 1
  );

  array<SmallTownAirports, 2> airports;
  for (auto& x : airports) {
    x = static_cast<SmallTownAirports>(gen_airport(rnd));
  }

  uint64_t total = 0;
  for (int step = 0; step < 100'000'000; ++step) {
    AirportCounter<SmallTownAirports> counter(begin(airports), end(airports));
    total += counter.Get(SmallTownAirports::Airport_1);
    for (const auto [airport, count] : counter.GetItems()) {
      total += count;
    }
  }
  // Assert to use variable total so that compiler doesn't optimize it out
  ASSERT(total > 0);
}

void TestMostPopularAirport() {
  default_random_engine rnd(20180624);
  uniform_int_distribution<size_t> gen_airport(
    0, static_cast<size_t>(SmallCountryAirports::Last_) - 1
  );

  array<pair<SmallCountryAirports, SmallCountryAirports>, 1000> dayly_flight_report;
  for (auto& x : dayly_flight_report) {
    x = {
      static_cast<SmallCountryAirports>(gen_airport(rnd)),
      static_cast<SmallCountryAirports>(gen_airport(rnd))
    };
  }

  const int days_to_explore = 365 * 500;

  vector<SmallCountryAirports> most_popular(days_to_explore);

  for (int day = 0; day < days_to_explore; ++day) {
    AirportCounter<SmallCountryAirports> counter;
    for (const auto& [source, dest] : dayly_flight_report) {
      counter.Insert(source);
      counter.Insert(dest);
    }

    const auto items = counter.GetItems();
    most_popular[day] = max_element(begin(items), end(items), [](auto lhs, auto rhs) {
      return lhs.second < rhs.second;
    })->first;
  }

  ASSERT(all_of(begin(most_popular), end(most_popular), [&](SmallCountryAirports a) {
    return a == most_popular.front();
  }));
}

int main() {
  TestRunner tr;

  // ÐŸÐ¾ ÑƒÑÐ»Ð¾Ð²Ð¸ÑŽ, ÑÑƒÐ¼Ð¼Ð°Ñ€Ð½Ð¾Ðµ Ð²Ñ€ÐµÐ¼Ñ Ñ€Ð°Ð±Ð¾Ñ‚Ñ‹ Ð²ÑÐµÑ… Ñ‚ÐµÑÑ‚Ð¾Ð² Ð½Ðµ Ð´Ð¾Ð»Ð¶Ð½Ð¾ Ð¿Ñ€ÐµÐ²Ñ‹ÑˆÐ°Ñ‚ÑŒ
  // Ð´Ð²ÑƒÑ… ÑÐµÐºÑƒÐ½Ð´. Ð•ÑÐ»Ð¸ Ð²Ð°ÑˆÐµ Ð²Ñ€ÐµÐ¼Ñ Ð±ÑƒÐ´ÐµÑ‚ Ð»Ð¸ÑˆÑŒ Ñ‡ÑƒÑ‚ÑŒ Ð±Ð¾Ð»ÑŒÑˆÐµ Ð´Ð²ÑƒÑ… ÑÐµÐºÑƒÐ½Ð´,
  // Ð¿Ð¾Ð¿Ñ€Ð¾Ð±ÑƒÐ¹Ñ‚Ðµ Ð¾Ñ‚Ð¿Ñ€Ð°Ð²Ð¸Ñ‚ÑŒ Ð²Ð°ÑˆÐµ Ñ€ÐµÑˆÐµÐ½Ð¸Ðµ Ð² Ñ‚ÐµÑÑ‚Ð¸Ñ€ÑƒÑŽÑ‰ÑƒÑŽ ÑÐ¸ÑÑ‚ÐµÐ¼Ñƒ. Ð’Ð¾Ð·Ð¼Ð¾Ð¶Ð½Ð¾,
  // Ñ‚Ð°Ð¼ Ð±Ð¾Ð»ÐµÐµ Ð¼Ð¾Ñ‰Ð½Ð¾Ðµ Ð¶ÐµÐ»ÐµÐ·Ð¾, Ð¸ Ð²Ð°ÑˆÐµ Ñ€ÐµÑˆÐµÐ½Ð¸Ðµ Ð±ÑƒÐ´ÐµÑ‚ Ð¿Ñ€Ð¸Ð½ÑÑ‚Ð¾.
  
  // ÐšÑ€Ð¾Ð¼Ðµ Ñ‚Ð¾Ð³Ð¾, Ð½Ðµ Ð·Ð°Ð±ÑƒÐ´ÑŒÑ‚Ðµ Ð²ÐºÐ»ÑŽÑ‡Ð¸Ñ‚ÑŒ Ð¾Ð¿Ñ‚Ð¸Ð¼Ð¸Ð·Ð°Ñ†Ð¸Ð¸ Ð¿Ñ€Ð¸ ÐºÐ¾Ð¼Ð¿Ð¸Ð»ÑÑ†Ð¸Ð¸ ÐºÐ¾Ð´Ð°.

  //LOG_DURATION("Total tests duration");
  RUN_TEST(tr, TestMoscow);
  RUN_TEST(tr, TestManyConstructions);
  RUN_TEST(tr, TestManyGetItems);
  RUN_TEST(tr, TestMostPopularAirport);
  return 0;
}*/