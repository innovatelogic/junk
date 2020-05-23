#include "test_runner.h"

#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
#include <list>

using namespace std;

template <typename T>
void ring_advance(typename std::list<T> &list, typename std::list<T>::iterator &iter, int steps)
{
    if (list.empty()){ 
        return;
    }

    if (iter == list.end()){
        iter = list.begin();
    }

    for (; steps > 0; --steps)
    {
        ++iter;

        if (iter == list.end()){
            iter = list.begin();
        }
    }
}

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) 
{
    std::list<typename RandomIt::value_type> list;

    for (auto it = first; it != last; ++it){
        list.push_back(std::move(*it));
    }

    size_t curr_pos = 0;

    const size_t inc = step_size - 1;

    auto it = list.begin();

    while (!list.empty())
    {
        *(first++) = std::move(*it);
        
        it = list.erase(it);

        ring_advance(list, it, step_size - 1);
    }
}
/*
vector<int> MakeTestVector()
{
  vector<int> numbers(10);
  iota(begin(numbers), end(numbers), 0);
  return numbers;
}

void TestIntVector() 
{
  const vector<int> numbers = MakeTestVector();
  {
    vector<int> numbers_copy = numbers;
    MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
    ASSERT_EQUAL(numbers_copy, numbers);
  }
  {
    vector<int> numbers_copy = numbers;
    MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
    ASSERT_EQUAL(numbers_copy, vector<int>({0, 3, 6, 9, 4, 8, 5, 2, 7, 1}));
  }
}

// Ð­Ñ‚Ð¾ ÑÐ¿ÐµÑ†Ð¸Ð°Ð»ÑŒÐ½Ñ‹Ð¹ Ñ‚Ð¸Ð¿, ÐºÐ¾Ñ‚Ð¾Ñ€Ñ‹Ð¹ Ð¿Ð¾Ð¼Ð¾Ð¶ÐµÑ‚ Ð²Ð°Ð¼ ÑƒÐ±ÐµÐ´Ð¸Ñ‚ÑŒÑÑ, Ñ‡Ñ‚Ð¾ Ð²Ð°ÑˆÐ° Ñ€ÐµÐ°Ð»Ð¸Ð·Ð°Ñ†Ð¸Ñ
// Ñ„ÑƒÐ½ÐºÑ†Ð¸Ð¸ MakeJosephusPermutation Ð½Ðµ Ð²Ñ‹Ð¿Ð¾Ð»Ð½ÑÐµÑ‚ ÐºÐ¾Ð¿Ð¸Ñ€Ð¾Ð²Ð°Ð½Ð¸Ðµ Ð¾Ð±ÑŠÐµÐºÑ‚Ð¾Ð².
// Ð¡ÐµÐ¹Ñ‡Ð°Ñ Ð²Ñ‹, Ð²Ð¾Ð·Ð¼Ð¾Ð¶Ð½Ð¾, Ð½Ðµ Ð¿Ð¾Ð½Ð¸Ð¼Ð°ÐµÑ‚Ðµ ÐºÐ°Ðº Ð¾Ð½ ÑƒÑÑ‚Ñ€Ð¾ÐµÐ½, Ð¾Ð´Ð½Ð°ÐºÐ¾ Ð¼Ñ‹ Ñ€Ð°ÑÑÐºÐ°Ð¶ÐµÐ¼,
// Ð¿Ð¾Ñ‡ÐµÐ¼Ñƒ Ð¾Ð½ ÑƒÑÑ‚Ñ€Ð¾ÐµÐ½ Ð¸Ð¼ÐµÐ½Ð½Ð¾ Ñ‚Ð°Ðº, Ð´Ð°Ð»ÐµÐµ Ð² Ð±Ð»Ð¾ÐºÐµ Ð¿Ñ€Ð¾ move-ÑÐµÐ¼Ð°Ð½Ñ‚Ð¸ÐºÑƒ â€”
// Ð² Ð²Ð¸Ð´ÐµÐ¾ Â«ÐÐµÐºÐ¾Ð¿Ð¸Ñ€ÑƒÐµÐ¼Ñ‹Ðµ Ñ‚Ð¸Ð¿Ñ‹Â»

struct NoncopyableInt
{
  int value;

  NoncopyableInt(const NoncopyableInt&) = delete;
  NoncopyableInt& operator=(const NoncopyableInt&) = delete;

  NoncopyableInt(NoncopyableInt&&) = default;
  NoncopyableInt& operator=(NoncopyableInt&&) = default;
};

bool operator == (const NoncopyableInt& lhs, const NoncopyableInt& rhs) {
  return lhs.value == rhs.value;
}

ostream& operator << (ostream& os, const NoncopyableInt& v) {
  return os << v.value;
}

void TestAvoidsCopying() 
{
  vector<NoncopyableInt> numbers;
  numbers.push_back({1});
  numbers.push_back({2});
  numbers.push_back({3});
  numbers.push_back({4});
  numbers.push_back({5});

  MakeJosephusPermutation(begin(numbers), end(numbers), 2);

  vector<NoncopyableInt> expected;
  expected.push_back({1});
  expected.push_back({3});
  expected.push_back({5});
  expected.push_back({4});
  expected.push_back({2});

  ASSERT_EQUAL(numbers, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  RUN_TEST(tr, TestAvoidsCopying);
  return 0;
}*/