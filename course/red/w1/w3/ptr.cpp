#include "test_runner.h"

#include <algorithm>
#include <numeric>
#include <cmath>


using namespace std;

template <typename T>
void Swap(T* first, T* second)
{
    T tmp = *first;
    *first = *second;
    *second = tmp;
}

template <typename T>
void SortPointers(vector<T*> &pointers)
{
    std::sort(pointers.begin(), pointers.end(), [](const T *lhs, const T *rhs){
        return *lhs < *rhs;
    });
}

template <typename T>
void ReversedCopy(T* source, size_t count, T* destination)
{
    T *src_start = source;
    T *src_end = src_start + count;

    T *dst_start = destination;
    T *dst_end = dst_start + count;

    //std::cout << "[] same array" << std::endl;
      if (dst_start >= src_end || dst_end <= src_start)
      {
        std::reverse_copy(src_start, src_end, dst_start);
      }
      // source on the left
      else if (src_start < dst_start)
      {
          T *s_lhs = src_start;
          T *d_rhs = dst_end - 1;

          while (s_lhs != dst_start){
            *(d_rhs--) = *(s_lhs++);
          }

         /* for (size_t i = 0; src_start + i < dst_start; ++i) {
            *(dst_end - i - 1) = *(src_start + i);
          }
*/
          std::reverse(dst_start, src_end);
      }
      else // source on the right
      {

         /* for (size_t i = 0; src_end - i - 1 >= dst_end; ++i) {
            *(dst_start + i) = *(src_end - i - 1);
          }*/

          T *s_rhs = src_end - 1;
          T *d_lhs = dst_start;

          while (d_lhs != src_start)
          {
            *(d_lhs++) = *(s_rhs--);
          }

          std::reverse(src_start, dst_end);
      }
}

void TestSwap() {
  int a = 1;
  int b = 2;
  Swap(&a, &b);
  ASSERT_EQUAL(a, 2);
  ASSERT_EQUAL(b, 1);

  string h = "world";
  string w = "hello";
  Swap(&h, &w);
  ASSERT_EQUAL(h, "hello");
  ASSERT_EQUAL(w, "world");
}

void TestSortPointers() {
  int one = 1;
  int two = 2;
  int three = 3;

  vector<int*> pointers;
  pointers.push_back(&two);
  pointers.push_back(&three);
  pointers.push_back(&one);

  SortPointers(pointers);

  ASSERT_EQUAL(pointers.size(), 3u);
  ASSERT_EQUAL(*pointers[0], 1);
  ASSERT_EQUAL(*pointers[1], 2);
  ASSERT_EQUAL(*pointers[2], 3);
}

void TestReverseCopy() {
  const size_t count = 7;

  int* source = new int[count];
  int* dest = new int[count];

  for (size_t i = 0; i < count; ++i) {
    source[i] = dest[i] =  i + 1;
    
  }
  
  ReversedCopy(source, count, dest);
  const vector<int> expected1 = {7, 6, 5, 4, 3, 2, 1};
  ASSERT_EQUAL(vector<int>(dest, dest + count), expected1);

  {
  ReversedCopy(source, count - 1, source + 1);
  const vector<int> expected2 = {1, 6, 5, 4, 3, 2, 1};
  ASSERT_EQUAL(vector<int>(source, source + count), expected2);
  }

  {
  ReversedCopy(source, count, source);
  const vector<int> expected2 = {7, 6, 5, 4, 3, 2, 1};
  ASSERT_EQUAL(vector<int>(source, source + count), expected2);
  }

  delete[] dest;
  delete[] source;
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSwap);
  RUN_TEST(tr, TestSortPointers);
  RUN_TEST(tr, TestReverseCopy);
  return 0;
}