#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iterator>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    auto dist = std::distance(range_begin, range_end);

    if (dist < 2){
        return;
    }

    const size_t _third = std::distance(range_begin, range_end) / 3;

    //std::vector<typename RandomIt::value_type> tmp_vec(std::make_move_iterator(range_begin), std::make_move_iterator(range_end));

    //auto tmp_begin = tmp_vec.begin();

    std::vector<typename RandomIt::value_type> v0(std::make_move_iterator(range_begin), std::make_move_iterator(range_begin + _third));
    std::vector<typename RandomIt::value_type> v1(std::make_move_iterator(range_begin + _third), std::make_move_iterator(range_begin + (2 * _third)));
    std::vector<typename RandomIt::value_type> v2(std::make_move_iterator(range_begin + (2 * _third)), std::make_move_iterator(range_end));

    MergeSort(std::begin(v0), std::end(v0));
    MergeSort(std::begin(v1), std::end(v1));
    MergeSort(std::begin(v2), std::end(v2));

    std::vector<typename RandomIt::value_type> tmp;

    std::merge(std::make_move_iterator(std::begin(v0)),
               std::make_move_iterator(std::end(v0)),
               std::make_move_iterator(std::begin(v1)),
               std::make_move_iterator(std::end(v1)),
               std::back_inserter(tmp));

    std::merge(std::make_move_iterator(std::begin(tmp)),
               std::make_move_iterator(std::end(tmp)),
               std::make_move_iterator(std::begin(v2)),
               std::make_move_iterator(std::end(v2)),
               range_begin);
}
/*
int main()
{
    std::vector<int> v = {8, 6, 4, 7, 6, 4, 4, 0, 1};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return 0;
}*/