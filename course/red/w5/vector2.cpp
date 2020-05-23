//#include "test_runner.h"

#include <iostream>
#include <algorithm>
#include <utility>
#include <string>
#include <cstring>

using namespace std;

template <typename T>
class SimpleVector
{
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
    
  void PushBack(T value)
  {
      //std::cerr << "add 0" << std::endl;

    if (m_end == m_data + m_capacity)
    {
        ///std::cerr << "add 1" << std::endl;

        size_t new_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;

        T *new_data = new T[new_capacity];

        move(begin(), end(), new_data);

        delete [] m_data;
        
        m_data = new_data;

        m_end = m_data + m_capacity;

        m_capacity = new_capacity;

        //std::cerr << "add 2" << std::endl;
    }

    //std::cerr << "add 3" << std::endl;

    *(m_end++) = std::move(value);

    //std::cerr << "add 4" << std::endl;
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

void TestPushBack() {
  SimpleVector<int> v;
  for (int i = 10; i >= 1; --i) {
    v.PushBack(i);
    ASSERT(v.Size() <= v.Capacity());
  }
  sort(begin(v), end(v));

  const vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ASSERT(equal(begin(v), end(v), begin(expected)));
}

class StringNonCopyable : public string {
public:
  using string::string;
  StringNonCopyable(string&& other) : string(move(other)) {}
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  SimpleVector<StringNonCopyable> strings;
  static const int SIZE = 10;
  for (int i = 0; i < SIZE; ++i) {
    strings.PushBack(StringNonCopyable(to_string(i)));
  }

  for (int i = 0; i < SIZE; ++i) {
    ASSERT_EQUAL(strings[i], to_string(i));
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestConstruction);
  RUN_TEST(tr, TestPushBack);
  RUN_TEST(tr, TestNoCopy);
  return 0;
}*/