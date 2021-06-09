#include <iostream>
#include <vector>
#include <set>
#include <functional>
#include <limits>
#include <assert.h>


void foreach_path(const std::vector<std::vector<int>> &arrays, 
                  int d,
                  int &curr_min,
                  std::multiset<int>& min_max,
                  const std::function<void()> &callback,
                  int parent)
{
    if (d == arrays.size()){
        callback();
        return;
    }

    for (auto i : arrays[d]){

        min_max.insert(i);

        int min = *min_max.rbegin() - *min_max.begin();

        if (min > curr_min && i > parent){

            std::cout << "overflow : " << *min_max.rbegin() << " " << *min_max.begin() << " (" << min << " > " << curr_min << ") break " << d << std::endl;

            min_max.erase(i);
            return;
        }

        foreach_path(arrays, d + 1, curr_min, min_max, callback, i);

        min_max.erase(i);
    }
}

std::vector<int> arrays_min_intersection(const std::vector<std::vector<int>> &arrays)
{
    std::vector<int> out(arrays.size());

    assert(arrays.size() > 0);

    int min_scalar = std::numeric_limits<int>::max();

    std::multiset<int> min_max;

    int iterations = 0;

    for (auto i : arrays[0])
    {
       min_max.insert(i);

       foreach_path(arrays, 1, min_scalar, min_max, [&](){
            
            iterations++;

            int min = *min_max.rbegin() - *min_max.begin();

            if (min < min_scalar)
            {
                std::cout << "min : " << *min_max.rbegin() << " " << *min_max.begin() <<  " = " << min << std::endl;

                min_scalar = min;

                int n = 0;
                for (int k : min_max)
                {
                    out[n++] = k;
                }
            }
        }, i);

        min_max.erase(i);
    }

    std::cout << "iterations : " << iterations << std::endl; 

    return out;
}


int main()
{
    std::vector<std::vector<int>> arr = {
      {5, 10, 15},
      {3, 6, 9, 12, 15, 80},
      {8, 16, 24}  
    };

    auto out = arrays_min_intersection(arr);

    for (auto i : out)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}