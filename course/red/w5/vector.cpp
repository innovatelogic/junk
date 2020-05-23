//#include "test_runner.h"

#include <iostream>
#include <algorithm>
#include <utility>
#include <string>
#include <cstring>

using namespace std;


template <typename T>
class SimpleVector {
public:
  SimpleVector()
  : m_data(nullptr)
  , m_end(nullptr)
  , m_capacity(0)
  {
  }

  explicit SimpleVector(size_t size)
  {
      if (size > 0){
          m_data = new T [size];
      }

        m_capacity = size;
        m_end = m_data + size;
  }

  SimpleVector(const SimpleVector &rhs)
  {
    if (rhs.Size() > 0){
        m_data = new T [rhs.Capacity()];
    }

    std::copy(rhs.begin(), rhs.end(), begin());

    m_capacity = rhs.m_capacity;
    m_end = m_data + rhs.Size();
  }

  void operator=(const SimpleVector& rhs)
  {
    if (rhs.Capacity() <= m_capacity)
    {
      std::copy(rhs.begin(), rhs.end(), begin());
      m_end = m_data + rhs.Size();
    } else {

      SimpleVector<T> tmp(rhs); 
      std::swap(tmp.m_data, m_data);
      std::swap(tmp.m_capacity, m_capacity);
      m_end = m_data + rhs.Size();
    }
  }

  ~SimpleVector()
  {
      delete [] m_data;
  }

  T& operator[](size_t index) { return m_data[index]; }

  const T* begin() const { return m_data; }
  const T* end() const { return m_end; }

  T* begin() { return m_data; }
  T* end() { return m_end; }

  size_t Size() const { return m_end - m_data; }

  size_t Capacity() const { return m_capacity; }
    
  void PushBack(const T& value)
  {
      if (m_data == nullptr)
      {
          m_data = new T[1];
          *m_data = value;
          m_capacity = 1;
          m_end = m_data + 1;
      }
      else
      {
          if (m_end == m_data + m_capacity)
          {
            size_t new_capacity = m_capacity * 2;
            
            T *new_data = new T[new_capacity];

            std::copy(begin(), end(), new_data);
            //std::memcpy((void*)new_data, (const void*)m_data, sizeof(T) * m_capacity);

            delete [] m_data;

            m_data = new_data;

            m_end = m_data + m_capacity;

            m_capacity = new_capacity;
          }

          *(m_end++) = value;
      }
      
  }

private:
    T *m_data;
    T *m_end;
    size_t m_capacity;
};


/*
void TestConstruction() {
  SimpleVector<int> empty;
  ASSERT_EQUAL(empty.Size(), 0u);
  ASSERT_EQUAL(empty.Capacity(), 0u);
  ASSERT(empty.begin() == empty.end());

  SimpleVector<string> five_strings(5);
  ASSERT_EQUAL(five_strings.Size(), 5u);
  ASSERT(five_strings.Size() <= five_strings.Capacity());
  for (auto& item : five_strings) {
    ASSERT(item.empty());
  }
  five_strings[2] = "Hello";
  ASSERT_EQUAL(five_strings[2], "Hello");
}

void TestPushBack() 
{
  SimpleVector<int> v;
  for (int i = 10; i >= 1; --i) 
  {
    std::cout << i << std::endl;

    v.PushBack(i);
    ASSERT(v.Size() <= v.Capacity());
  }
  sort(begin(v), end(v));

  const vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ASSERT_EQUAL(v.Size(), expected.size());
  ASSERT(equal(begin(v), end(v), begin(expected)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestConstruction);
  RUN_TEST(tr, TestPushBack);
  return 0;
}*/