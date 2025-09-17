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


//-------------------------------------------------------
std::string remove_chars_2(std::string &str, const std::string &to_remove)
{
    std::unordered_set<char> hash_to_rm;
    for (size_t i = 0; i < to_remove.size(); ++i){
        hash_to_rm.insert(to_remove[i]);
    }
    // tow pointer pattern
    // dst - current write position
    // curr - string iterator
    // dst is always less or equal 
    
    // curr - fast pointer
    // dest - slow pointer
    // [dest - curr] - sliding window range
    // 0 .... [dest - curr] ... N
    // invariant:
    // dst and curr point to first element 
    // for each symbol:
    //      read str[curr] to tmp
    //      if tmp is not marked to delete:
    //          revrite str[dst] with tmp

    size_t dst = 0;
    size_t curr = 0;
    while (curr < str.size())
    {
        auto tmp = str[curr];  // save curr symbol to temp variable
        if (hash_to_rm.count(tmp) == 0){
            str[dst++] = tmp; // pack symbol to array's begin. Invariant preserves becouse dst <= curr and str[curr] is stored and can be revritten 
        }
        curr++;
    }

    if (dst != curr){
        str.resize(dst);
    }

    return str;
}

TEST(Remove_chars, Test2)
{
    {
        auto str = std::string("tetter");
        EXPECT_EQ(remove_chars_2(str, std::string("te")), "r");
    }

    {
        auto str = std::string("tetter");
        EXPECT_EQ(remove_chars_2(str, std::string("ter")), "");
    }

    {
        auto str = std::string("tetter");
        EXPECT_EQ(remove_chars_2(str, std::string("")), "tetter");
    }
}


std::string remove_chars_17_09_25(std::string &str, const std::string &to_remove)
{
    std::unordered_set<char> hash_to_rm;
    for (auto c : to_remove){
        hash_to_rm.insert(c);
    }

    int last = 0;
    for (int i = 0; i < str.size(); ++i)
    {
        if (hash_to_rm.count(str[i]) == 0){
            str[last++] = str[i];
        }
    }

    str.resize(last);

    return str;
}

TEST(Remove_chars, Test_17_09_25)
{
    {
        auto str = std::string("tetter");
        EXPECT_EQ(remove_chars_17_09_25(str, std::string("te")), "r");
    }

    {
        auto str = std::string("tetter");
        EXPECT_EQ(remove_chars_17_09_25(str, std::string("ter")), "");
    }

    {
        auto str = std::string("tetter");
        EXPECT_EQ(remove_chars_17_09_25(str, std::string("")), "tetter");
    }
}
}