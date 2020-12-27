#include "test_runner.h"

#include <algorithm>
#include <cstddef>  // нужно для nullptr_t

using namespace std;

// Реализуйте шаблон класса UniquePtr
template <typename T>
class UniquePtr
{
private:
  T * m_ptr;

public:
  UniquePtr()
  : m_ptr(nullptr)
  {}

  UniquePtr(T * ptr)
  : m_ptr(ptr)
  {}

  UniquePtr(const UniquePtr&) = delete;

  UniquePtr(UniquePtr&& other)
  {
      if (this != &other)
      {
        m_ptr = other.m_ptr;
        other.m_ptr = nullptr;
      }
  }

  UniquePtr& operator = (const UniquePtr&) = delete;

  UniquePtr& operator = (nullptr_t)
  {
      safe_release();
      return *this;
  }

  UniquePtr& operator = (UniquePtr&& other)
  {
      if (this != &other)
      {
        safe_release();
        m_ptr = other.m_ptr;
        other.m_ptr = nullptr;
      }

      return *this;
  }

  ~UniquePtr()
  {
      safe_release();
  }

  T& operator * () const
  {
      return *m_ptr;
  }

  T * operator -> () const { return m_ptr; }

  T * Release() 
  {
      T *cpy = m_ptr;
      m_ptr = nullptr;
      return cpy;
  }

  void Reset(T * ptr)
  {
      safe_release();
      m_ptr = ptr;
  }

  void Swap(UniquePtr& other)
  {
      std::swap(m_ptr, other.m_ptr);
  }

  T * Get() const { return m_ptr; }

  private:
    void safe_release()
    {
      if (m_ptr != nullptr) {
        delete m_ptr;
        m_ptr = nullptr;
      }
    }
};

/*
struct Item {
  static int counter;
  int value;
  Item(int v = 0): value(v) {
    ++counter;
  }
  Item(const Item& other): value(other.value) {
    ++counter;
  }
  ~Item() {
    --counter;
  }
};

int Item::counter = 0;


void TestLifetime() {
  Item::counter = 0;
  {
    UniquePtr<Item> ptr(new Item);
    ASSERT_EQUAL(Item::counter, 1);

    ptr.Reset(new Item);
    ASSERT_EQUAL(Item::counter, 1);
  }
  ASSERT_EQUAL(Item::counter, 0);

  {
    UniquePtr<Item> ptr(new Item);
    ASSERT_EQUAL(Item::counter, 1);

    auto rawPtr = ptr.Release();
    ASSERT_EQUAL(Item::counter, 1);

    delete rawPtr;
    ASSERT_EQUAL(Item::counter, 0);
  }
  ASSERT_EQUAL(Item::counter, 0);
}

void TestGetters() {
  UniquePtr<Item> ptr(new Item(42));
  ASSERT_EQUAL(ptr.Get()->value, 42);
  ASSERT_EQUAL((*ptr).value, 42);
  ASSERT_EQUAL(ptr->value, 42);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestLifetime);
  RUN_TEST(tr, TestGetters);
}*/


/*

#include <cstddef>
#include <utility>

template <typename T>
class UniquePtr {
private:
  T* ptr_;

public:
  UniquePtr() : ptr_(nullptr) {}
  UniquePtr(T * ptr) : ptr_(ptr) {}
  UniquePtr(const UniquePtr&) = delete;
  UniquePtr(UniquePtr&& other) : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
  }
  UniquePtr& operator = (const UniquePtr&) = delete;
  UniquePtr& operator = (std::nullptr_t) {
    Reset(nullptr);
    return *this;
  }
  UniquePtr& operator = (UniquePtr&& other) {
    if (this != &other) {
      Reset(other.ptr_);
      other.ptr_ = nullptr;
    }
    return *this;
  }
  ~UniquePtr() {
    delete ptr_;
  }
  T& operator * () const {
    return *ptr_;
  }
  T * operator -> () const {
    return ptr_;
  }
  T * Release() {
    auto result = ptr_;
    ptr_ = nullptr;
    return result;
  }
  void Reset(T * ptr) {
    delete ptr_;
    ptr_ = ptr;
  }
  void Swap(UniquePtr& other) {
    std::swap(ptr_, other.ptr_);
  }
  T * Get() const {
    return ptr_;
  }
};

*/