#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>

std::set<int>::const_iterator FindNearestElement(const std::set<int> &numbers, int border)
{
    auto not_less = numbers.lower_bound(border);
    
    if (not_less == numbers.begin())
    {
        return not_less;
    }

    const auto less = std::prev(not_less);
    if (not_less == numbers.end())
    {
        return less;
    }
     
    const bool is_left = (border - *less <= *not_less - border);
    return is_left ? less : not_less;
}


int main()
{
    std::set<int> numbers = {1, 4, 6};
    std::cout << *FindNearestElement(numbers, 0) << " " << std::endl;

    std::cout << *FindNearestElement(numbers, 3) << " " << std::endl;
    std::cout << *FindNearestElement(numbers, 5) << std::endl;
    std::cout << *FindNearestElement(numbers, 6) << " " << std::endl;
    std::cout << *FindNearestElement(numbers, 100)  << " " << std::endl;
      
    std::set<int> empty_set;
  
    std::cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << std::endl;
    return 0;
}