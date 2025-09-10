#include <gtest/gtest.h>
#include <string>
#include <unordered_set>




namespace junk
{

// two pointers pattern  

// tetter. [t,e]
// eetter
// tetter
//

std::string remove_chars(std::string &str, const std::string &to_remove)
{
    std::unordered_set<char> hash_to_remove;

    for (size_t i = 0; i < to_remove.size(); ++i){
        hash_to_remove.insert(to_remove[i]);
    }

    // invariant:
    // dst - is never larger than src
    // dst <= src
    // Algorithm divides by 3 window ranges
    // [0......dst) [dst - src] (src ..... N)
    // 1: [0......dst) Already done window - always fit algorithm requirements
    // 2: [dst - src] - Algorithm working sliding window. Part where swaps performs
    // 3: (src ..... N) - Untouched area
    size_t dst = 0;
    for (size_t src = 0; src < str.size(); ++src)
    {
        if (hash_to_remove.count(str[src]) == 0){
            str[dst++] = str[src];
        }
    }

    str.resize(dst);
    return str;
}

TEST(Remove_chars, Test1)
{
    {
        auto str = std::string("tetter");
        EXPECT_EQ(remove_chars(str, std::string("te")), "r");
    }

     {
        auto str = std::string("tetter");
        EXPECT_EQ(remove_chars(str, std::string("ter")), "");
    }
}


}