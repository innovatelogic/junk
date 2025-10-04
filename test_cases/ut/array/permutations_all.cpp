#include <gtest/gtest.h>
#include <functional>
#include <string>
#include <stack>
#include <cmath>

using namespace std::string_literals;

class permutator_041025
{
public:
    permutator_041025(const std::string &src)
    : m_used(src.size(), false)
    , source(src)
    {
        m_index_mask.reserve(src.size());
    }

    void backtrack(const std::function<void(const std::vector<int64_t>&)> &callback)
    {
        backtrack_impl(callback);
    }

private:
    void backtrack_impl(const std::function<void(const std::vector<int64_t>&)> &callback)
    {
        if (m_index_mask.size() == source.size()){
            callback(m_index_mask);
            return;
        }

        for (int i = 0; i < source.size(); ++i)
        {
            if (m_used[i]) { continue; }
            
            m_index_mask.push_back(i);
            m_used[i] = true;

            backtrack_impl(callback);

            m_used[i] = false;
            m_index_mask.pop_back();
        }
    }

private:
    std::vector<int64_t> m_index_mask;

    std::stack<int64_t> m_stack;
    std::vector<bool> m_used;
    const std::string &source;
};

TEST(Permutator, 041025)
{
    {
        const auto lit{"abcd"s};
        permutator_041025 p(lit);
        size_t count = 0;
        p.backtrack([&](const std::vector<int64_t>& m)
        {
            for (auto idx : m){
                std::cout << lit[idx];
            }
            std::cout << std::endl;
            ++count;
        });
        EXPECT_EQ(count, std::tgamma(lit.size() + 1));
    }
}