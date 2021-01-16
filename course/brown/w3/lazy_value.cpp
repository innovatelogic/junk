#include "test_runner.h"

#include <functional>
#include <string>
#include <mutex>

using namespace std;

template <typename T>
class LazyValue {
public:
  explicit LazyValue(std::function<T()> init)
  : m_value(nullptr)
  , m_init_func(std::move(init))
  {}

  LazyValue(const LazyValue &src)
  {
      m_value = src.m_value;
      m_init_func = src.m_init_func;
  }

  LazyValue(const LazyValue &&src)
  {
      m_value = std::move(src.m_value);
      m_init_func = std::move(src.m_init_func);
  }

  ~LazyValue()
  {
      delete m_value;
  }

  bool HasValue() const { return m_value != nullptr; }
  
  const T& Get() const
  {
      std::lock_guard<std::mutex> lock(m_mutex);

      if (!m_value){
          m_value = new T(m_init_func());
      }

      return *m_value;
  }

private:
    mutable T *m_value;
    std::function<T()>  m_init_func;
    mutable std::mutex m_mutex;
};

void UseExample() {
  const string big_string = "Giant amounts of memory";

  LazyValue<string> lazy_string([&big_string] { return big_string; });

  ASSERT(!lazy_string.HasValue());
  ASSERT_EQUAL(lazy_string.Get(), big_string);
  ASSERT_EQUAL(lazy_string.Get(), big_string);
}

void TestInitializerIsntCalled() {
  bool called = false;

  {
    LazyValue<int> lazy_int([&called] {
      called = true;
      return 0;
    });
  }
  ASSERT(!called);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, UseExample);
  RUN_TEST(tr, TestInitializerIsntCalled);
  return 0;
}

/*
#include <functional>
#include <optional>
using namespace std;

template <typename T>
class LazyValue {
public:
  explicit LazyValue(std::function<T()> init) : init_(std::move(init)) {
  }

  bool HasValue() const {
    return value_.has_value();
  }

  const T& Get() const {
    if (!value_) {
      value_ = init_();
    }
    return *value_;
  }

private:
  std::function<T()> init_;
  mutable std::optional<T> value_;
};
*/