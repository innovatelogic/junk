#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <map>
#include <deque>

using namespace std;

template <typename T>
class PriorityCollection {
public:
   using Id = size_t; //typename std::map<size_t, typename T>::const_iterator;

    PriorityCollection()
    : m_ids(0)
    {
        m_priority_id_map[0] = {};
    }
    
    Id Add(T object)
    {
        auto ins_iter = m_id_object_map.insert(std::make_pair(m_ids, std::move(object)));

        m_priority_id_map[0].push_back(m_ids);

        m_id_priority_map[m_ids] = 0;

        return m_ids++;
    }

    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin)
    {
        while(range_begin != range_end)
        {
            auto ins_iter = m_id_object_map.insert(std::make_pair(m_ids, std::move(*range_begin)));

            m_priority_id_map[0].push_back(m_ids);

            m_id_priority_map[m_ids] = 0;

            *ids_begin++ = m_ids;

            m_ids++;

            ++range_begin;
        }
    }

  bool IsValid(Id id) const
  {
        return m_id_object_map.find(id) != m_id_object_map.end();
  }

  const T& Get(Id id) const
  {
        return m_id_object_map.at(id);
  }

  void Promote(Id id)
  {
      // remove from 
      auto iter_find_priority = m_id_priority_map.find(id);

      size_t prev_priority = iter_find_priority->second++;

      // remove from prev deque
      auto &prev_deque = m_priority_id_map[prev_priority];

      auto deq_find = std::find(std::begin(prev_deque), std::end(prev_deque), id);

      prev_deque.erase(deq_find);

      if (prev_deque.empty()) 
      {
          m_priority_id_map.erase(prev_priority);
      }

      auto iter_new_priority = m_priority_id_map.find(prev_priority + 1);

      if (iter_new_priority != m_priority_id_map.end())
      {
          iter_new_priority->second.push_back(id);
      }
      else
      {
          m_priority_id_map[prev_priority + 1] = {id};
      }
  }

  pair<const T&, int> GetMax() const
  {
      auto max_iter = m_priority_id_map.rbegin(); 

      auto iter_max_id = std::max_element(max_iter->second.begin(), max_iter->second.end());

      size_t unique_id = *iter_max_id;

      return {m_id_object_map.at(unique_id), max_iter->first};
  }

  pair<T, int> PopMax()
  {
      auto max_iter = m_priority_id_map.rbegin();

      auto iter_max_id = std::max_element(max_iter->second.begin(), max_iter->second.end());

      size_t unique_id = *iter_max_id;

      std::pair<T, int> out = {std::move(m_id_object_map[unique_id]), max_iter->first};

      max_iter->second.erase(iter_max_id);


      if (max_iter->second.empty()) 
      {
          m_priority_id_map.erase(max_iter->first);
          //std::cerr << "clear priority: " << max_iter->first << std::endl;
      }

      m_id_priority_map.erase(unique_id);

      m_id_object_map.erase(unique_id);

      return out;
  }

/*
  void print()
  {
      for (auto const it : m_priority_id_map)
      {
          std::cout << "priority :" << it.first << std::endl;

          for (auto id : it.second)
          {
              std::cout << m_id_object_map[id] << ' ';
          }

          std::cout << std::endl;
      }
  }*/

private:
    std::map<Id, T> m_id_object_map;

    std::map<size_t, std::deque<Id>> m_priority_id_map;

    std::map<Id, size_t> m_id_priority_map;
    
    size_t m_ids;  
};


class StringNonCopyable : public string 
{
public:
  using string::string;  // ÐŸÐ¾Ð·Ð²Ð¾Ð»ÑÐµÑ‚ Ð¸ÑÐ¿Ð¾Ð»ÑŒÐ·Ð¾Ð²Ð°Ñ‚ÑŒ ÐºÐ¾Ð½ÑÑ‚Ñ€ÑƒÐºÑ‚Ð¾Ñ€Ñ‹ ÑÑ‚Ñ€Ð¾ÐºÐ¸
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy()
{
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  //strings.print();

  strings.Promote(yellow_id);

  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);

  //strings.print();

  {
    const auto item = strings.PopMax();
    //std::cerr << " 1: " << item.first << std::endl;

    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  //strings.print();
  {
    const auto item = strings.PopMax();

    std::cerr << " 2: " << item.first << std::endl;
    ASSERT_EQUAL(item.first, "yellow");
    
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}


void TestVVV()
{
    PriorityCollection<StringNonCopyable> strings;

    std::vector<std::string> out = {"white", "y", "r"};
    std::vector<size_t> out_(3);

    strings.Add(std::begin(out), std::end(out), std::begin(out_));

    auto max = strings.GetMax();
}

int main() 
{
  TestRunner tr;
  RUN_TEST(tr, TestVVV);
  return 0;
}