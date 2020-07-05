#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <list>
#include <tuple>
#include <unordered_set>

using namespace std;

struct Record {
  string id;
  string title;
  string user;
  int timestamp;
  int karma;

  bool operator==(const Record &other) const {
      return std::tie(id, title, user, timestamp, karma) ==
                std::tie(other.id, other.user, other.title, other.timestamp, other.karma);
  }
};

class RecordHasher {
  size_t operator()(const Record& r) const 
  {
    const hash<string> shash;
    return shash(r.id);
  }
};

class RecordIterHasher {
public:
  size_t operator()(const list<Record>::iterator& rit) const {
    hash<string> shash;
    return shash(rit->id);
  }
};

// Ð ÐµÐ°Ð»Ð¸Ð·ÑƒÐ¹Ñ‚Ðµ ÑÑ‚Ð¾Ñ‚ ÐºÐ»Ð°ÑÑ
class Database 
{
public:
  bool Put(const Record& record)
  {
      if (m_table.count(record.id) != 0)
      {
          return false;
      }
      else
      {
          m_records.push_back(record);
          auto it_last = std::prev(m_records.end());

          m_table[record.id] = it_last;

          m_timestamp_f_key[record.timestamp].insert(it_last);
          m_karma_f_key[record.karma].insert(it_last);
          m_user_f_key[record.user].insert(it_last);
      }
    return true;
  }

  const Record* GetById(const string& id) const
  {
      const Record *rec = nullptr;
      auto iter_find = m_table.find(id);
      if (iter_find != m_table.end())
      {
          rec = &*iter_find->second;
      }
      return rec;
  }

  bool Erase(const string& id)
  {
      if (m_table.count(id) == 0)
      {
          return false;
      }
      else
      {
          auto record = m_table.at(id);
          m_timestamp_f_key[record->timestamp].erase(m_table.at(record->id));
          m_karma_f_key[record->karma].erase(m_table.at(record->id));
          m_user_f_key[record->user].erase(m_table.at(record->id));
          m_records.erase(record);
          m_table.erase(id);
      }
      return true;
  }

  template <typename Callback>
  void RangeByTimestamp(int low, int high, Callback callback) const
  {
      auto lb = m_timestamp_f_key.lower_bound(low);
      auto ub = m_timestamp_f_key.upper_bound(high);

      for (auto it = lb; it != ub; ++it)
      {
        for (const auto& it_h : it->second) {
          if (!callback(*it_h)) {
              return;
          }
        }
      }
  }

  template <typename Callback>
  void RangeByKarma(int low, int high, Callback callback) const
  {
      auto lb = m_karma_f_key.lower_bound(low);
      auto ub = m_karma_f_key.upper_bound(high);

      for (auto it = lb; it != ub; ++it)
      {
        for (const auto& it_h : it->second) {
          if (!callback(*it_h)) {
              return;
          }
        }
      }
  }

  template <typename Callback>
  void AllByUser(const string& user, Callback callback) const
  {
    auto ret = m_user_f_key.equal_range(user);
    
    for (auto it = ret.first; it != ret.second; ++it)
      {
        for (const auto& it_h : it->second) {
          if (!callback(*it_h)) {
              return;
          }
        }
      }
  }

  protected:
  private:

    
    using TListRecords = std::list<Record>;
    using TMapRecords = std::unordered_map<std::string, TListRecords::iterator>;
    
    TListRecords m_records;

    TMapRecords m_table;

    std::map<int, std::unordered_set<TListRecords::iterator, RecordIterHasher>> m_timestamp_f_key;
    std::map<int, std::unordered_set<TListRecords::iterator, RecordIterHasher>> m_karma_f_key;
    std::map<std::string, std::unordered_set<TListRecords::iterator, RecordIterHasher>> m_user_f_key;
};

void TestRangeBoundaries() 
{
  const int good_karma = 1000;
  const int bad_karma = -10;

  Database db;
  db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
  db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

  int count = 0;
  db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
    ++count;
    return true;
  });
    //std::cout << count << std::endl;
  ASSERT_EQUAL(2, count);
}

void TestSameUser() {
  Database db;
  db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
  db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

  int count = 0;
  db.AllByUser("master", [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestReplacement() {
  const string final_body = "Feeling sad";

  Database db;
  db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
  db.Erase("id");
  db.Put({"id", final_body, "not-master", 1536107260, -10});

  auto record = db.GetById("id");
  ASSERT(record != nullptr);
  ASSERT_EQUAL(final_body, record->title);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestRangeBoundaries);
  RUN_TEST(tr, TestSameUser);
  RUN_TEST(tr, TestReplacement);
  return 0;
}