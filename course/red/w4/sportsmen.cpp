
#include <iomanip>
#include <iostream>
#include <list>
#include <map>

class Queue
{

public:
    void Add(int number, int before)
    {
        auto iter_find = m_nodes.find(before);
        if (iter_find == m_nodes.end())
        {
            m_list.push_back(number);

            std::list<int>::iterator last = m_list.end();
            --last;
            m_nodes[number] = last;
        }
        else
        {
            m_nodes[number] = m_list.insert(iter_find->second, number);

        }   
    }

    void Print()
    {
       for (const auto &i : m_list)
       {
           std::cout << i << " ";
       } 
    }

protected:
private:
    std::list<int> m_list;
    std::map<int, std::list<int>::iterator> m_nodes;
};

int main() 
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Queue queue_list;

    int query_count;
    std::cin >> query_count;

    while(query_count > 0)
    {
        int num, before;
        std::cin >> num >> before;

        queue_list.Add(num, before);

        --query_count;
    }

    queue_list.Print();

    return 0;
}
