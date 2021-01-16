#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <array>
#include <map>
#include <string>


#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>

using namespace std;

class ReadingManager {
public:
  ReadingManager()
        // -1 значит, что не случилось ни одного READ
      : user_page_counts_(MAX_USER_COUNT_ + 1, -1),
        page_achieved_by_count_(MAX_PAGE_COUNT_ + 1, 0) {}

  void Read(int user_id, int page_count) {
    UpdatePageRange(user_page_counts_[user_id] + 1, page_count + 1);
    user_page_counts_[user_id] = page_count;
  }

  double Cheer(int user_id) const {
    const int pages_count = user_page_counts_[user_id];
    if (pages_count == -1) { 
      return 0;
    }
    const int user_count = GetUserCount();
    if (user_count == 1) {
      return 1;
    }
    // По умолчанию деление целочисленное, поэтому
    // нужно привести числитель к типу double.
    // Простой способ сделать это — умножить его на 1.0.
    return (user_count - page_achieved_by_count_[pages_count]) * 1.0
           / (user_count - 1);
  }

private:
  // Статическое поле не принадлежит какому-либо конкретному объекту класса. 
  // По сути это глобальная переменная, в данном случае - константная.
  // Будь она публичной, к ней можно было бы обратиться снаружи
  // следующим образом: ReadingManager::MAX_USER_COUNT.
  static const int MAX_USER_COUNT_ = 100'000;
  static const int MAX_PAGE_COUNT_ = 1'000;

  // Номер страницы, до которой дочитал пользователь <ключ>
  vector<int> user_page_counts_;
  // Количество пользователей, дочитавших (как минимум) до страницы <индекс>
  vector<int> page_achieved_by_count_;

  int GetUserCount() const {
    return page_achieved_by_count_[0];
  }
  
  // lhs включительно, rhs не включительно
  void UpdatePageRange(int lhs, int rhs) { 
    for (int i = lhs; i < rhs; ++i) {
      ++page_achieved_by_count_[i];
    }
  }
};


int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}
/*
using namespace std;

class ReadingManager {
public:
  ReadingManager()
      : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
        sorted_users_(),
        user_positions_(MAX_USER_COUNT_ + 1, -1)
        , m_user_count(0)
        {
            for (int i = 0; i < MAX_USER_COUNT_; i++)
            {
                m_users[i] = {0, 0};
            }

            for (size_t i = 0; i < 1000; i++)
            {
                m_page_readers[i] = 0;
            }

        }

  void Read(int user_id, int page_count) 
  {
      if (page_count == 0){
          return;
      }

      if (m_users[user_id].first == 0)
      {
          m_users[user_id] = {user_id, page_count};
          ++m_user_count;
          ++m_page_readers[page_count];
      }
      else
      {
          --m_page_readers[m_users[user_id].second];
          m_users[user_id].second = page_count;
          ++m_page_readers[m_users[user_id].second];
      }

      m_cached_page_rate.clear();
    
  }

  double Cheer(int user_id) const 
  {
    if (m_users[user_id].first == 0) {
        return 0;
    }

    if (m_user_count == 1){
        return 1.0;
    }

    const size_t &user_page = m_users[user_id].second;

    //std::cout << "user_page : " << user_page << std::endl;

   // if (!m_cached_page_rate.empty() && user_page <= m_cached_page_rate.rbegin()->first)
    //{
    //    std::cout << "found cached : " << std::endl;
    
    //    return m_cached_page_rate[user_page];
    //}

    size_t total_count = 0;
    for (size_t idx = 0; idx < user_page; ++idx)
    {
       // std::cout << "page readers : " << m_page_readers[idx] << std::endl;

        total_count += m_page_readers[idx];
        //m_cached_page_rate[idx] = total_count * 1.0 / m_user_count;
    }

     //std::cout << "total readers : " << total_count << " user_count: " <<  m_user_count << std::endl;
    return (total_count * 1.0) / (m_user_count - 1);
  // return m_cached_page_rate[user_page];
  }

private:
  // Статическое поле не принадлежит какому-то конкретному
  // объекту класса. По сути это глобальная переменная,
  // в данном случае константная.
  // Будь она публичной, к ней можно было бы обратиться снаружи
  // следующим образом: ReadingManager::MAX_USER_COUNT.
  static const int MAX_USER_COUNT_ = 100'000;

  vector<int> user_page_counts_;
  vector<int> sorted_users_;   // отсортированы по убыванию количества страниц
  vector<int> user_positions_; // позиции в векторе sorted_users_

  std::array<std::pair<int, size_t>, MAX_USER_COUNT_> m_users;
  std::array<size_t, 1000>                            m_page_readers;
  size_t                                              m_user_count;
  mutable std::map<size_t, double>                    m_cached_page_rate;

  int GetUserCount() const {
    return sorted_users_.size();
  }
  void AddUser(int user_id) {
    sorted_users_.push_back(user_id);
    user_positions_[user_id] = sorted_users_.size() - 1;
  }
  void SwapUsers(int lhs_position, int rhs_position) {
    const int lhs_id = sorted_users_[lhs_position];
    const int rhs_id = sorted_users_[rhs_position];
    swap(sorted_users_[lhs_position], sorted_users_[rhs_position]);
    swap(user_positions_[lhs_id], user_positions_[rhs_id]);
  }
};
*/