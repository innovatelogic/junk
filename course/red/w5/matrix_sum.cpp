//#include "test_runner.h"
#include <vector>
#include <future>
#include <numeric>
#include <cmath>

using namespace std;

template <class Iterator>
class IteratorRange
{
public:  
    IteratorRange(Iterator begin, Iterator end)
    : _begin(begin)
    , _end(end)
    {}

    //Iterator begin() { return _begin; }
    //Iterator end() { return _end; }

    Iterator begin() const { return _begin; }
    Iterator end() const { return _end; }

    size_t size() const { return std::distance(begin(), end()); }

    Iterator _begin;
    Iterator _end;
};

template <typename Iterator>
class Paginator 
{
public:
  Paginator(Iterator begin, Iterator end, size_t page_size)
  : _begin(begin)
  , _end(end)
  , _page_size(page_size)
  {
      const size_t size = std::distance(begin, end);
      const size_t chunks = std::ceil((float)size / page_size);

      auto idx_last = size - 1;

      for (int chunk = 0; chunk < chunks; ++chunk)
      {
        auto idx_offset = chunk * page_size;
        
        Iterator first = begin + idx_offset;
        
        Iterator last = first + ((idx_offset + page_size <= idx_last) ? (page_size - 1) : idx_last - idx_offset);

        pages.push_back(IteratorRange<Iterator>(first, last + 1));
      }
  }

  auto begin() { return pages.begin(); }
  auto end() { return pages.end(); }

  //typename std::vector<IteratorRange<Iterator>>::const_iterator begin() const { return pages.begin(); }
  //typename std::vector<IteratorRange<Iterator>>::const_iterator end() const { return pages.end(); }

  size_t size() const { return pages.size(); }

private:  
  Iterator _begin;
  Iterator _end;
  size_t _page_size;

  std::vector<IteratorRange<Iterator>> pages;
};

using TMatrix = std::vector<std::vector<int>>;
int64_t CalculateMatrixSum(const vector<vector<int>>& matrix)
{
    Paginator<TMatrix::const_iterator> paginator(matrix.begin(), matrix.end(), 2500);

    std::vector<std::future<int64_t>> futures;

    for (auto &page : paginator)
    {
        futures.push_back(async([&page]
        {
            int64_t sum = 0;
            for(auto &p : page){
                sum += std::accumulate(p.begin(), p.end(), 0);
            }
            return sum;
        }));
    }

    int64_t res = 0;
    for (auto &f : futures)
    {
        res += f.get();
    }

    return res;
}
/*
void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
}*///