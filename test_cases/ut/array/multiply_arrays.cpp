#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

std::vector<int> mult_arrays(std::vector<int> &arr1, std::vector<int> &arr2)
{
    if (arr1.empty() || arr2.empty()){
        return {};
    }

    bool sign = arr1.front() < 0 ^ arr2.front() < 0;

    arr1.front() = std::abs(arr1.front());
    arr2.front() = std::abs(arr2.front());

    std::vector<int> out(arr1.size() + arr2.size(), 0);

    for (int i = arr2.size() - 1, k = 0; i >= 0; --i, ++k)
    {
        for (int j = arr1.size() - 1; j >= 0; --j)
        {
            std::cout << ">> i=" << i << ", j=" << j << " k=" << k << std::endl;
            out[i + j + 1] += arr2[i] * arr1[j];

            out[i + j] += out[i + j + 1] / 10;
            out[i + j + 1] %= 10;
        }
    }

    out = {std::find_if(std::begin(out), std::end(out), [](auto v){
        return v != 0;
    }), std::end(out)};

    if (out.empty()){
        return {0};
    }

    if (sign){
        out[0] *= -1;
    }

    return out;
}

TEST(MultArray, Test_240925)
{
    {
        std::vector<int> a1{1, 0, 1};
        std::vector<int> a2{2, 2};
        const std::vector<int> eq{2, 2, 2, 2};
        EXPECT_EQ(mult_arrays(a1, a2), eq);
    }

    {
        std::vector<int> a1{1, 0, 1};
        std::vector<int> a2{-2, 2};
        const std::vector<int> eq{-2, 2, 2, 2};
        EXPECT_EQ(mult_arrays(a1, a2), eq);
    }

    {
        std::vector<int> a1{0};
        std::vector<int> a2{-2, 2};
        const std::vector<int> eq{0};
        EXPECT_EQ(mult_arrays(a1, a2), eq);
    }

    {
        std::vector<int> a1{9, 9, 9};
        std::vector<int> a2{9, 9, 9};
        const std::vector<int> eq{9, 9, 8, 0, 0, 1};
        EXPECT_EQ(mult_arrays(a1, a2), eq);
    }
}