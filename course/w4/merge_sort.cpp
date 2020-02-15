#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    auto dist = std::distance(range_begin, range_end);
    //std::cout << "dist: " << std::distance(range_begin, range_end) << std::endl;

    if (dist < 2){
        return;
    }
/*
    if (dist == 2)
    {
        //std::cout << *range_begin << " <> " << *(range_begin + 1) << std::endl;
        if (*(range_begin + 1) < *(range_begin)){

            //std::cout << " swap: " << *range_begin << " <> " << *(range_begin + 1) << std::endl;
            std::swap(*range_begin, *(range_begin + 1));
           // typename RandomIt::value_type t = *(range_begin + 1);
            //*(range_begin + 1) =  *(range_begin);
            //*(range_begin) = t;
        }

        return;
    }*/

    const size_t mid = std::distance(range_begin, range_end) / 2;

    std::vector<typename RandomIt::value_type> v0(range_begin, range_begin + mid);
    std::vector<typename RandomIt::value_type> v1(range_begin + mid, range_end);

    MergeSort(std::begin(v0), std::end(v0));
    MergeSort(std::begin(v1), std::end(v1));

    std::merge(std::begin(v0), std::end(v0), std::begin(v1), std::end(v1), range_begin);
}

int main()
{
    std::vector<int> v = {8, 6, 4, 7, 6, 4, 4, 0, 1};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return 0;
}