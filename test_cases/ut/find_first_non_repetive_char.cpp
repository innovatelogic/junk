

#include <gtest/gtest.h>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <limits>

// hash lookup pattern

namespace junk
{


std::pair<bool, char> find_first_non_repetetive(const std::string &str)
{
    std::pair<bool, char> out{false, '\0'};
    if (str.empty()) { 
        return out;
    }

    std::unordered_map<char, int> hash_symbol_count;

    for (int i = 0; i < str.size(); ++i){
        
        if (hash_symbol_count.count(str[i]) == 0){
            hash_symbol_count[str[i]] = 1;
        }
        else{
            hash_symbol_count[str[i]]++;
        }
    }

    for (int i = 0; i < str.size(); ++i){
        if (hash_symbol_count[str[i]] == 1){ 
            out = {true, str[i]};
        }
    }

    return out;
}


std::pair<bool, char> find_first_non_repetetive2(const std::string &str)
{
    std::pair<bool, char> out{false, '\0'};
    if (str.empty()) { 
        return out;
    }

    std::unordered_map<char, std::pair<int, int>> hash_symbol_count_order;

    for (int i = 0; i < str.size(); ++i){
        
        if (hash_symbol_count_order.count(str[i]) == 0){
            hash_symbol_count_order[str[i]] = {1, i};
        }
        else{
            hash_symbol_count_order[str[i]].first++;
        }
    }

    int pos = std::numeric_limits<int>::max();
    for (auto it = hash_symbol_count_order.begin(); it != hash_symbol_count_order.end(); ++it){
        if (it->second.first == 1 && it->second.second < pos){ 
            pos = it->second.second;
        }
    }

    if (pos < std::numeric_limits<int>::max()){
        out = {true, str[pos]};
    }
    return out;
}


TEST(Find_first_non_repetetive, Test1)
{

    {
        auto eq = std::pair<bool, char>{true, 'r'};
        EXPECT_EQ(find_first_non_repetetive("tetter"), eq);
        EXPECT_EQ(find_first_non_repetetive2("tetter"), eq);
    }

     {
        auto eq = std::pair<bool, char>{false, '\0'};
        EXPECT_EQ(find_first_non_repetetive("tertter"), eq);
        EXPECT_EQ(find_first_non_repetetive2("tertter"), eq);
    }

}

}