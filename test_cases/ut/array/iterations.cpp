#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <limits>


namespace junk{


std::vector<std::pair<int, int>> iter_align_right(const std::vector<int> &lhs, const std::vector<int> &rhs)
{
    std::vector<std::pair<int, int>> out;

    auto max_len = std::max(lhs.size(), rhs.size());
    auto delta = max_len - std::min(lhs.size(), rhs.size());

    // lhs: 0, 1, 2, 3, 4
    // rhs:       0, 1, 2
    // diff= 2

    auto idx = max_len;
    
    while (idx > 0)
    {
        --idx;

        auto idx_lhs = (lhs.size() >= rhs.size()) ? idx : ( (idx >= delta) ? idx - delta : std::numeric_limits<size_t>::max() );
        auto idx_rhs = (rhs.size() >= lhs.size()) ? idx : ( (idx >= delta) ? idx - delta : std::numeric_limits<size_t>::max() );

        auto v_l = idx_lhs != std::numeric_limits<size_t>::max() ? lhs[idx_lhs] : 0;
        auto v_r = idx_rhs != std::numeric_limits<size_t>::max() ? rhs[idx_rhs] : 0;

        out.emplace_back(std::pair<int, int>{v_l, v_r});
    } 
    
    std::reverse(out.begin(), out.end());

    return out;
}   


TEST(ArrayIter, Test1_Indexed)
{
    {
        std::vector<int> l{};
        std::vector<int> r{};
        
        const std::vector<std::pair<int, int>> res{};

        EXPECT_EQ(iter_align_right(l, r), res);
    }

    {
        std::vector<int> l{0, 1, 2, 3, 4};
        std::vector<int>       r{0, 1, 2};

        const std::vector<std::pair<int, int>> res{{0, 0}, {1, 0}, {2, 0}, {3, 1}, {4, 2}};

        EXPECT_EQ(iter_align_right(l, r), res);

    }

    {
        std::vector<int> l{0, 1, 2, 3, 4};
        std::vector<int>      r{0, 1, 2};

        const std::vector<std::pair<int, int>> res{{0, 0}, {1, 0}, {2, 0}, {3, 1}, {4, 2}};

        EXPECT_EQ(iter_align_right(l, r), res);

    }

    {
        std::vector<int> l{};
        std::vector<int> r{0, 1, 2, 3, 4};
        
        const std::vector<std::pair<int, int>> res{{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}};

        EXPECT_EQ(iter_align_right(l, r), res);
    }
}


std::vector<std::pair<int, int>> iter_align_right_2(const std::vector<int> &lhs, const std::vector<int> &rhs)
{
    std::vector<std::pair<int, int>> out(std::max(lhs.size(), rhs.size()));

    auto it_l = lhs.rbegin();
    auto it_r = rhs.rbegin();

    size_t idx = out.size() - 1;
    while (it_l != std::rend(lhs) || it_r != std::rend(rhs))
    {
        auto v_l = it_l != std::rend(lhs) ? *it_l++ : 0;
        auto v_r = it_r != std::rend(rhs) ? *it_r++ : 0;

        out[idx--] = {v_l, v_r};
    }
    return out;
}


TEST(ArrayIter, Test_Iter)
{
    {
        std::vector<int> l{};
        std::vector<int> r{};
        
        const std::vector<std::pair<int, int>> res{};

        EXPECT_EQ(iter_align_right_2(l, r), res);
    }

    {
        std::vector<int> l{0, 1, 2, 3, 4};
        std::vector<int>       r{0, 1, 2};

        const std::vector<std::pair<int, int>> res{{0, 0}, {1, 0}, {2, 0}, {3, 1}, {4, 2}};

        EXPECT_EQ(iter_align_right_2(l, r), res);

    }

    {
        std::vector<int> l{0, 1, 2, 3, 4};
        std::vector<int>      r{0, 1, 2};

        const std::vector<std::pair<int, int>> res{{0, 0}, {1, 0}, {2, 0}, {3, 1}, {4, 2}};

        EXPECT_EQ(iter_align_right_2(l, r), res);

    }

    {
        std::vector<int> l{};
        std::vector<int> r{0, 1, 2, 3, 4};
        
        const std::vector<std::pair<int, int>> res{{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}};

        EXPECT_EQ(iter_align_right_2(l, r), res);
    }
}

}