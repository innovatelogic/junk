#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <array>
#include <set>
#include <string>
#include <map>
#include <queue>

class BookingManager
{
    static const int FRAMES_IN_DAY = 86400;

    struct booking
    {
        long int time;
        std::string name;
        int client_id;
        int rooms;
    };
    
public:
    BookingManager()
    {}

    void Book(long int time, const std::string &name, int client_id, int rooms)
    {
        m_frames.push({time, name, client_id, rooms});

        m_rooms[name] += rooms;

        m_clients[name][client_id]++;

        Update();
    }

    int Clients(const std::string &name)
    {
        return m_clients[name].size();
    }

    int Rooms(const std::string &name)
    {
        return m_rooms[name];
    }

protected:
    void Update()
    {
        long int curr = m_frames.back().time;

        while (curr - m_frames.front().time >= FRAMES_IN_DAY)
        {
            const auto &book = m_frames.front();

            m_rooms[book.name] -= book.rooms;

            m_clients[book.name][book.client_id]--;

            if (m_clients[book.name][book.client_id] == 0){
                m_clients[book.name].erase(book.client_id);
            }

            m_frames.pop();
        }
    }

private:
    std::queue<booking> m_frames;
    std::map<std::string, int> m_rooms;
    std::map<std::string, std::map<int, int>> m_clients;
};



int main() 
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  BookingManager manager;

  int query_count;
  std::cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) 
  {
    std::string query_type;
    std::cin >> query_type;

    if (query_type == "BOOK") 
    {
        long int time;
        std::string name;
        int client_id;
        int rooms;

        std::cin >> time >> name >> client_id >> rooms;

        manager.Book(time, name, client_id, rooms);
    } 
    else if (query_type == "CLIENTS")
    {
        std::string name;
        std::cin >> name;
        std::cout << manager.Clients(name) << "\n";
    }
    else if (query_type == "ROOMS")
    {
        std::string name;
        std::cin >> name;
        std::cout << manager.Rooms(name) << "\n";
    }
  }

  return 0;
}