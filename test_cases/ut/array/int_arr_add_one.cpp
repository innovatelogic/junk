#include <gtest/gtest.h>
#include <vector>
#include <iostream>

// 0, 1, 3
//

void add_one_230925(std::vector<int> &arr)
{
    if (arr.empty()) {
        arr = {0};
    }

    (*arr.rbegin())++;


    for (int i = arr.size() - 1; i >= 0; --i)
    {
        bool next = arr[i] >= 10;

        arr[i] %= 10;

        if (next)
        {
            (i > 0) ? (arr[i - 1]++, 0) : (arr.insert(arr.begin(), 1), 0);
        }
    }
}

TEST(AddOne, Test_230925)
{
    {
        std::vector<int> arr{};
        add_one_230925(arr);
        const std::vector<int> eq{1};
        EXPECT_EQ(arr, eq);
    }

    {
        std::vector<int> arr{0, 1, 2};
        add_one_230925(arr);
        const std::vector<int> eq{0, 1, 3};
        EXPECT_EQ(arr, eq);
    }

    {
        std::vector<int> arr{9, 9, 9};
        add_one_230925(arr);
        const std::vector<int> eq{1, 0, 0, 0};
        EXPECT_EQ(arr, eq);
    }
}

void add_one_09242025(std::vector<int> &arr)
{
    if (arr.empty()){
        arr = {1};
        return;
    }

    arr.back()++;

    for (auto i = arr.size() - 1; i > 0 && arr[i] == 10;  --i) {
        arr[i] = 0;
        arr[i - 1]++;
    }

    if (arr[0] == 10){
        arr[0] = 0;
        arr.insert(arr.begin(), 1);
    }

}

TEST(AddOne, Test_240925)
{
    {
        std::vector<int> arr{};
        add_one_09242025(arr);
        const std::vector<int> eq{1};
        EXPECT_EQ(arr, eq);
    }

    {
        std::vector<int> arr{0, 1, 2};
        add_one_09242025(arr);
        const std::vector<int> eq{0, 1, 3};
        EXPECT_EQ(arr, eq);
    }

    {
        std::vector<int> arr{9, 9, 9};
        add_one_09242025(arr);
        const std::vector<int> eq{1, 0, 0, 0};
        EXPECT_EQ(arr, eq);
    }
}