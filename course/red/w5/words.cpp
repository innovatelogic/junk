#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <functional> 

using namespace std;


template <typename String>
using Group = vector<String>;

template <typename String>
using Char = typename String::value_type;

/*template<typename String>
int metric(typename String::iterator begin, typename String::iterator end)
{
    int out = 0;
    for (;begin != end; begin++)
    {
        out += *begin;
    }
    return out;
}*/

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings)
{
    vector<Group<String>> out_vec;

    std::map<String, Group<String>> out_groups;

    for (auto &str : strings)
    {
        String cpy(str);

        std::sort(cpy.begin(), cpy.end());
        cpy.erase(std::unique(cpy.begin(), cpy.end()), cpy.end());

        auto iter_find = out_groups.find(cpy);
        if (iter_find == out_groups.end())
        {
            std::vector<String> tmp;
            tmp.push_back(std::move(str));

            out_groups.emplace(std::make_pair(std::move(cpy), std::move(tmp)));
        }
        else
        {
            iter_find->second.emplace_back(std::move(str));
        }
    }

    for (auto &v : out_groups){
        out_vec.push_back(std::move(v.second));
    }

    return out_vec;
}
/*

void TestGroupingABC() 
{
  vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 2);
  sort(begin(groups), end(groups));  // ÐŸÐ¾Ñ€ÑÐ´Ð¾Ðº Ð³Ñ€ÑƒÐ¿Ð¿ Ð½Ðµ Ð¸Ð¼ÐµÐµÑ‚ Ð·Ð½Ð°Ñ‡ÐµÐ½Ð¸Ñ
  ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
  ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal() 
{
  vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 4);
  sort(begin(groups), end(groups));  // ÐŸÐ¾Ñ€ÑÐ´Ð¾Ðº Ð³Ñ€ÑƒÐ¿Ð¿ Ð½Ðµ Ð¸Ð¼ÐµÐµÑ‚ Ð·Ð½Ð°Ñ‡ÐµÐ½Ð¸Ñ
  ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
  ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
  ASSERT_EQUAL(groups[2], vector<string>({"port"}));
  ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestGroupingABC);
  RUN_TEST(tr, TestGroupingReal);
  return 0;
}*/