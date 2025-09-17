

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

//----------------------------------------------------------------
std::pair<bool, char> find_firs_non_repetetive_3(const std::string &str)
{
    std::pair<bool, char> out{false, '\0'};

    std::unordered_map<char, std::pair<size_t, size_t>> hash_symbol_count_pos;


    for (size_t i = 0; i < str.size(); ++i){
        if (hash_symbol_count_pos.count(str[i]) == 0) {
            hash_symbol_count_pos[str[i]] = {1, i};
        }
        else{
            auto &p = hash_symbol_count_pos[str[i]];
            p.first++;
        }
    }

    auto max_pos = std::numeric_limits<size_t>::max();
    for (auto it = hash_symbol_count_pos.begin(); it != hash_symbol_count_pos.end(); ++it)
    {
        if (it->second.first == 1 && it->second.second < max_pos){
            max_pos = it->second.second;
        }
    }

    if (max_pos != std::numeric_limits<size_t>::max()) {
        out = {true, str[max_pos]};
    }

    return out;
}


TEST(Find_first_non_repetetive, Test2)
{
    {
        auto eq = std::pair<bool, char>{true, 'r'};
        EXPECT_EQ(find_firs_non_repetetive_3("tetter"), eq);
    }

     {
        auto eq = std::pair<bool, char>{false, '\0'};
        EXPECT_EQ(find_firs_non_repetetive_3("tertter"), eq);
    }

}

std::pair<bool, char> find_first_not_repettetive_4(const std::string &str)
{
    std::unordered_map<char, std::pair<size_t, size_t>> hash_count_pos;

    for (size_t i = 0; i < str.size(); ++i) {

        auto [it, inserted] = hash_count_pos.try_emplace(str[i], 1, i);

        if (!inserted){
            it->second.first++;
        }
    }

    std::cout << "str=" << str << std::endl;
    const auto MAX = std::numeric_limits<size_t>::max();
    auto min_pos = MAX;
    for (const auto& [ch, data] : hash_count_pos) {
        if (data.first == 1 && data.second < min_pos){
            min_pos = data.second;
            std::cout << "[" << ch << "] count=" << data.first << ": pos=" << data.second << std::endl;
        }
    }

    if (min_pos != MAX) {
        return {true, str[min_pos]};
    }
    return {false, '\0'};
}

TEST(Find_first_non_repetetive, Test4)
{
    {
        auto eq = std::pair<bool, char>{true, 'r'};
        EXPECT_EQ(find_first_not_repettetive_4("tetter"), eq);
    }

     {
        auto eq = std::pair<bool, char>{false, '\0'};
        EXPECT_EQ(find_first_not_repettetive_4("tertter"), eq);
    }
}

std::pair<bool, char> find_first_not_repettetive_5(const std::string &str)
{
    std::pair<bool, char> res{false, '\0'};
    

    std::unordered_map<char, std::pair<size_t, size_t>> hash_count_pos;


    for (size_t i = 0; i < str.size(); ++i){

        if (hash_count_pos.count(str[i]) == 0){
            hash_count_pos[str[i]] = {1, i};
        }
        else {

            auto &pair = hash_count_pos[str[i]];
            pair.first++;
            pair.second = i;
        }
    }

    const auto MAX = std::numeric_limits<size_t>::max();
    size_t min_pos = MAX;

    for (auto v : hash_count_pos){

        auto &count = v.second.first;
        auto &pos = v.second.second;

        if (count == 1 && pos < min_pos){
            min_pos = pos;
        }
    }

    if (min_pos != MAX){
        res = {true, str[min_pos]};
    }


    return res;
}


TEST(Find_first_non_repetetive, Test5)
{
    {
        auto eq = std::pair<bool, char>{true, 'r'};
        EXPECT_EQ(find_first_not_repettetive_5("tetter"), eq);
    }

     {
        auto eq = std::pair<bool, char>{false, '\0'};
        EXPECT_EQ(find_first_not_repettetive_5("tertter"), eq);
    }

}

}