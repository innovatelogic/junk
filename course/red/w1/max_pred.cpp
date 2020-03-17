
#include <list>
#include <vector>
#include <iostream>

#include <algorithm>
#include <iterator>

template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred) 
{
    ForwardIterator find = first;

    bool flag = false;
    int n = 0;
    std::for_each(first, last, [&](const typename ForwardIterator::value_type &v)
    {
        if (pred(v) && (!flag || *find < v))
        {
            find = first;
            std::advance(find, n);
            flag = true;
        }

        ++n;
    });

    return flag ? find : last;
}

template <class ForwardIterator, class UnaryPredicate>
ForwardIterator __max_element_if(ForwardIterator first, ForwardIterator last, UnaryPredicate p)
{
  ForwardIterator maxElemIt = find_if(first, last, p);
  for (ForwardIterator cur = maxElemIt; cur != last; ++cur) {
    // cur != maxElemIt is checked to avoid re-calculation of p(*maxElemIt) at first iteration
    if (cur != maxElemIt && p(*cur) && *maxElemIt < *cur) {
      maxElemIt = cur;
    }
  }
  return maxElemIt;
}

/*
int main()
{
    auto IsEven = [](int x) {
        return x % 2 == 0;
    };

    //const std::list<int> hill{2, 4, 8, 9, 6, 4, 2};
    const std::list<int> hill{2, 1, 1, 1, 1, 1, 1};
    std::cout << *max_element_if(hill.begin(), hill.end(), IsEven);
}*/