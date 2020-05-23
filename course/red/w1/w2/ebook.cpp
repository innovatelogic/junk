#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <array>
#include <set>
#include <string>
#include <map>

using namespace std;

class ReadingManager 
{
public:
  ReadingManager()
      : m_user_ids(MAX_USER_COUNT_ + 1, 0)
      , m_user_page_pos(MAX_USER_COUNT_ + 1, 0)
      , m_user_count(0)
      , m_user_prev_count(MAX_USER_COUNT_ + 1, 0)
      , m_page_rating(1000, 0.0)
      , m_clear_cache(false)
    {
    }

  void Read(int user_id, int page_count) 
  {
    if (m_user_ids[user_id] == 0) 
    {
      AddUser(user_id);
    }
     
    std::map<int, std::set<int>>::iterator iter_pos = m_pages.find(page_count);

    if (iter_pos != m_pages.end() && iter_pos->second.find(user_id) != iter_pos->second.end()){
      return; // already there
    }

    // remove user from previous position
    const int prev_pos = m_user_page_pos[user_id];
    if (prev_pos != 0)
    {
      m_pages[prev_pos].erase(user_id);
      
      if (m_pages.empty()){
        m_pages.erase(prev_pos);
      }
    }

    // move user to next position
    if (iter_pos != m_pages.end())
    {
      iter_pos->second.insert(user_id);
    }else{
      m_pages[page_count].insert(user_id);
    }

    m_user_page_pos[user_id] = page_count;

    int prev_count = 0;
    for (auto iter_page = m_pages.begin(); iter_page != m_pages.end(); ++iter_page)
    {
      m_page_rating[iter_page->first] = (prev_count * 1.0) / (m_user_count - 1);

      prev_count += iter_page->second.size();
    }
  }

  double Cheer(int user_id) const 
  {
    if (m_user_ids[user_id] == 0) {
      return 0;
    }

    if (m_user_count == 1) {
      return 1;
    }

    return m_page_rating[m_user_page_pos[user_id]];

    //int prev_user_count = m_user_prev_count[user_id];

    /*std::map<int, std::set<int>>::const_iterator end = m_pages.find(m_user_page_pos[user_id]);
    for (auto iter = m_pages.begin(); iter != end; ++iter)
    {
      prev_user_count += iter->second.size();
    }*/

    //return (prev_user_count * 1.0) / (m_user_count - 1);
  }

private:
  int GetUserCount() const
  {
    return m_user_count;
  }

  void AddUser(int user_id) 
  {
    m_user_ids[user_id] = 1;
    ++m_user_count;
  }

  static const int MAX_USER_COUNT_ = 100'000;

  vector<int> m_user_ids;
  vector<int> m_user_page_pos;

  int m_user_count;
  std::map<int, std::set<int>> m_pages;

  vector<double> m_page_rating;
  mutable bool m_clear_cache;

  vector<int> m_user_prev_count;
};


int main () 
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id <query_count; ++ query_id) 
  {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") 
    {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } 
    else if (query_type == "CHEER") {
      cout << setprecision (6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}