#include <iostream>
#include <vector>
#include <algorithm>

// cl /EHsc mycode.cpp

void PrintVectorPart(const std::vector<int> &numbers)
{
    auto it_find = std::find_if(numbers.begin(), numbers.end(), [](int a) { return a < 0; });

    if (it_find != numbers.end())
    {
        for (auto it = std::make_reverse_iterator(it_find); it != numbers.rend(); ++it){
            std::cout << *it << " ";
        }
    }
    else
    {
        for (auto it = numbers.rbegin(); it != numbers.rend(); ++it){
            std::cout << *it << " ";
        }
    }
}

void PrintVectorPart2(const vector<int>& numbers) {
  auto negative_it = find_if(
    numbers.begin(), numbers.end(),
    [](int number) {
      return number < 0;
    }
  );

  for (auto it = negative_it; it != numbers.begin(); ) {
    cout << *(--it) << " ";
  }
}


int main()
{
    PrintVectorPart({6, 1, 8, -5, 4});
    std::cout << std::endl;
    PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
    std::cout << std::endl;
    PrintVectorPart({6, 1, 8, 5, 4});
    std::cout << std::endl;
    return 0;
}