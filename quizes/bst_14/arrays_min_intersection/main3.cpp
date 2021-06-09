#include <iostream>
#include <limits>
#include <map>
#include <vector>
#include <functional>


std::vector<int> arrays_min_intersection(const std::vector<std::vector<int>> &arrays)
{
    std::vector<int> out(arrays.size());

    int curr_min = std::numeric_limits<int>::max();

    std::multimap<int, std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator>, std::less<int>> frame;

    for (auto &v : arrays) {
        frame.insert({v[0], std::make_pair(v.begin(), v.end() - 1)});
    }

    while (1)
    {
        int min_max = frame.rbegin()->first - frame.begin()->first;

       // std::cout << "iter : " << min_max << std::endl;

       /* for (auto i = frame.begin(); i != frame.end(); ++i) {
            std::cout << *i->second.first << " ";
        }
        std::cout << std::endl;

        int a;
        std::cin >> a;*/

        if (min_max < curr_min){

            int n = 0;
            for (auto &k : frame){
                out[n++] = k.first;
            }
            curr_min = min_max;
        }

        bool reach_end = true;
        for (auto i = frame.begin(); i != frame.end(); ++i) {

            if (i->second.first == i->second.second){
                continue;
            }

            //std::cout << "min :" << *i->second.first << std::endl;
            i->second.first++;

            

            frame.insert({*i->second.first, std::make_pair(i->second.first, i->second.second)});
            frame.erase(i);

            reach_end = false;
            break;
        }

        if (reach_end){
            break;
        }
    }

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