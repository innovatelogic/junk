#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <algorithm>


namespace junk{

std::vector<int> sum(const std::vector<int> &l, const std::vector<int> &r)
{
    std::vector<int> out;

    auto len = std::max(l.size(), r.size());

    if (len == 0){
        return {0};
    }
    //  0, 1, 2, 3, 4, 5
    //  1, 2, 3, 4, 5, 6
    //           7, 8, 9

    int overflow = 0;

    auto l_it = l.rbegin();
    auto r_it = r.rbegin();

    do
    {
        auto v_l = l_it != std::rend(l) ? *l_it : 0;
        auto v_r = r_it != std::rend(r) ? *r_it : 0;

        auto sum = overflow + v_l + v_r;

        std::cout << "sum:" << sum << std::endl;

        out.push_back(sum % 10);

        overflow = sum >= 10 ? 1 : 0;

        if (l_it != std::rend(l)){
            l_it = std::next(l_it);
        }

        if (r_it != std::rend(r)){
            r_it = std::next(r_it);
        }

    } while(l_it != std::rend(l) || r_it != std::rend(r));

    if (overflow){
        out.push_back(1);
    }

    std::reverse(out.begin(), out.end());

    return out;
}

TEST(SumArray, Test1)
{
    {
        std::vector<int> a{1, 0, 0};
        std::vector<int> b{1, 2};

        auto res = sum(a, b);

        std::vector<int> r{1, 1, 2};
        EXPECT_EQ(res, r);
    }

    {
        std::vector<int> a{1, 0, 0};
        std::vector<int> b{0, 1, 2};

        auto res = sum(a, b);

        std::vector<int> r{1, 1, 2};
        EXPECT_EQ(res, r);
    }

    {
        std::vector<int> a{3, 0};
        std::vector<int> b{8, 2};

        auto res = sum(a, b);

        std::vector<int> r{1, 1, 2};
        EXPECT_EQ(res, r);
    }

    {
        std::vector<int> a{9, 9, 9, 9, 9, 9};
        std::vector<int> b{1};

        auto res = sum(a, b);

        std::vector<int> r{1, 0, 0, 0, 0, 0, 0};
        EXPECT_EQ(res, r);
    }
}



}