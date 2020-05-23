#include "test_runner.h"

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

template<typename T>
class Table
{
public:
    Table(size_t h, size_t w)
    : m_width(w)
    , m_height(h)
    {
        Resize(h, w);
    }

    std::pair<size_t, size_t> Size() const { return {m_height, m_width}; }

    std::vector<T>& operator[] (size_t r) {
        return m_table[r];
    }

    const std::vector<T>& operator[] (size_t r) const {
        return m_table[r];
    }

    void Resize(size_t h, size_t w)
    {
        std::vector<typename std::vector<T>> table(h);
        
        size_t row = 0;
        for (auto &r : table)
        {
            r.resize(w);

            if (row + 1 <= m_table.size())
            {
                typename std::vector<T>::const_iterator first = m_table[row].begin();
                typename std::vector<T>::const_iterator last = m_table[row].begin() + std::min(w, m_width);
                std::copy(first, last, r.begin());
            }
            ++row;
        }

        m_table = table;
        m_width = w;
        m_height = h;
    }

protected:
private:
    size_t m_width;
    size_t m_height;

    std::vector<std::vector<T>> m_table;
};
/*
void TestTable() 
{
  Table<int> t(1, 1);

  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);


  t[0][0] = 12;

  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  
  return 0;
}*/