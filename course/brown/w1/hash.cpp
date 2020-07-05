#include "test_runner.h"

#include <forward_list>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

template <typename Type, typename Hasher>
class HashSet 
{
public:
  using BucketList = forward_list<Type>;

public:
  explicit HashSet(
      size_t num_buckets,
      const Hasher& hasher = {}
  ) : m_hasher(hasher)
  {
      m_buckets.resize(num_buckets, {});
  }

  void Add(const Type& value)
  {
    size_t index = get_index(value);

    auto &bucket = m_buckets[index];

    auto iter_find = std::find(std::begin(bucket), std::end(bucket), value);

    if (iter_find == bucket.end()) {
        m_buckets[index].push_front(value);
    }
  }

  bool Has(const Type& value) const
  {
    size_t index = get_index(value);

    auto &bucket = m_buckets[index];

    auto iter_find = std::find(std::begin(bucket), std::end(bucket), value);
    return iter_find != bucket.end();
  }

  void Erase(const Type& value)
  {
      size_t index = get_index(value);

      auto &bucket = m_buckets[index];

      auto iter_find = std::find(std::begin(bucket), std::end(bucket), value);

      if (iter_find != bucket.end()) 
      {
          size_t list_index = std::distance(std::begin(bucket), iter_find);
          
          if (list_index == 0) {
              //std::cout << "erase begin" << std::endl;
              bucket.erase_after(bucket.before_begin());
          } else {
              //std::cout << "erase: " << list_index << std::endl;
              bucket.erase_after(std::next(bucket.begin(), list_index - 1));
          }
      }
  }

  const BucketList& GetBucket(const Type& value) const 
  {
      size_t index = get_index(value);

      return m_buckets[index];
  }
private:
    size_t get_index(const Type &value) const
    {
        return m_hasher(value) % m_buckets.size();
    }

private:
    std::vector<BucketList> m_buckets;
    const Hasher& m_hasher;
};

struct IntHasher {
  size_t operator()(int value) const
  {
    // Это реальная хеш-функция из libc++, libstdc++.
    // Чтобы она работала хорошо, std::unordered_map
    // использует простые числа для числа бакетов
    return value;
  }
};

struct TestValue 
{
  int value;

  bool operator==(TestValue other) const {
    return value / 2 == other.value / 2;
  }
};

struct TestValueHasher 
{
  size_t operator()(TestValue value) const {
    return value.value / 2;
  }
};
/*
void TestSmoke() {
  HashSet<int, IntHasher> hash_set(2);
  hash_set.Add(3);
  hash_set.Add(4);

  ASSERT(hash_set.Has(3));
  ASSERT(hash_set.Has(4));
  ASSERT(!hash_set.Has(5));

  hash_set.Erase(3);

  ASSERT(!hash_set.Has(3));
  ASSERT(hash_set.Has(4));
  ASSERT(!hash_set.Has(5));

  hash_set.Add(3);
  hash_set.Add(5);

  ASSERT(hash_set.Has(3));
  ASSERT(hash_set.Has(4));
  ASSERT(hash_set.Has(5));
}

void TestEmpty() {
  HashSet<int, IntHasher> hash_set(10);
  for (int value = 0; value < 10000; ++value) {
    ASSERT(!hash_set.Has(value));
  }
}

void TestIdempotency() {
  HashSet<int, IntHasher> hash_set(10);
  hash_set.Add(5);
  ASSERT(hash_set.Has(5));
  hash_set.Add(5);
  ASSERT(hash_set.Has(5));
  hash_set.Erase(5);
  ASSERT(!hash_set.Has(5));
  hash_set.Erase(5);
  ASSERT(!hash_set.Has(5));
}

void TestEquivalence()
 {
  HashSet<TestValue, TestValueHasher> hash_set(10);
  hash_set.Add(TestValue{2});
  hash_set.Add(TestValue{3});

  ASSERT(hash_set.Has(TestValue{2}));
  ASSERT(hash_set.Has(TestValue{3}));

  const auto& bucket = hash_set.GetBucket(TestValue{2});
  const auto& three_bucket = hash_set.GetBucket(TestValue{3});
  ASSERT_EQUAL(&bucket, &three_bucket);

  ASSERT_EQUAL(1, distance(begin(bucket), end(bucket)));
  ASSERT_EQUAL(2, bucket.front().value);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSmoke);
  RUN_TEST(tr, TestEmpty);
  RUN_TEST(tr, TestIdempotency);
  RUN_TEST(tr, TestEquivalence);
  return 0;
}*/