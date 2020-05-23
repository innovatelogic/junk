#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
#include <unordered_set>


using namespace std;

template <class T>
class ObjectPool 
{
public:
  T* Allocate()
  {
    T *p_out;

    // get deallocated
    if (!m_dealloc.empty())
    {
        p_out = m_dealloc.front();
        m_dealloc.pop();
    }
    else
    {
        p_out = new T();
    }
    
    m_alloc.insert(p_out);
    
    return p_out;
  }


  T* TryAllocate()
  {
    T *p_out = nullptr;

    // get deallocated
    if (!m_dealloc.empty())
    {
        p_out = m_dealloc.front();
        m_dealloc.pop();

        m_alloc.insert(p_out);
    }

    return p_out;
  }

  void Deallocate(T* object)
  {
      auto iter_find = m_alloc.find(object);

      if (iter_find == m_alloc.end())
      {
          throw std::invalid_argument("");
      }

      m_alloc.erase(object);

      m_dealloc.push(object);
  }

  ~ObjectPool()
  {
      while (!m_dealloc.empty())
      {
          T *p = m_dealloc.front();
          delete p;

          m_dealloc.pop();
      }

      for (auto *p : m_alloc){
          delete p;
      }
  }

private:
    std::unordered_set<T*> m_alloc;
    std::queue<T*> m_dealloc;
};
/*
void TestObjectPool() 
{
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}*/