#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <tuple>
#include <cstdint>
#include <vector>

// cl /EHsc mycode.cpp
/*
enum class Lang 
{
    DE,
    FR, 
    IT
};

struct Region 
{
    std::string std_name;
    std::string parent_std_name;
    std::map<Lang, std::string> names;
    int64_t population;
};
*/
bool operator<(const Region &lhs, const Region &rhs)
{
    return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
            tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

bool operator==(const Region &lhs, const Region &rhs)
{
    return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) ==
            tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

int FindMaxRepetitionCount(const std::vector<Region> &regions)
{
    /*auto rgn_copy = regions;
    std::sort(std::begin(rgn_copy), std::end(rgn_copy));
    auto it = std::unique(std::begin(rgn_copy), std::end(rgn_copy));
    rgn_copy.resize(std::distance(rgn_copy.begin(), it));
    return regions.size() - rgn_copy.size();*/
    int max = 0;

    std::map<Region, int> counts;

    for (auto &r : regions)
    {
        if (counts.count(r) == 0)
        {
            counts[r] = 1;

            max = std::max(max, counts[r]);
        }
        else
        {
            ++counts[r];
            max = std::max(max, counts[r]);
        }
    }
    return max;
}

int main()
{
    std::cout << FindMaxRepetitionCount({
    {
        "Moscow",
        "Russia",
        {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
        89
        }, {
        "Russia",
        "Eurasia",
        {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
        89
        }, {
        "Moscow",
        "Russia",
        {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
        89
        }, {
        "Moscow",
        "Russia",
        {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
        89
        }, {
        "Russia",
        "Eurasia",
        {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
        89
        },
    }) << std::endl;

    std::cout << FindMaxRepetitionCount({
    {
        "Moscow",
        "Russia",
        {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
        89
        }, {
        "Russia",
        "Eurasia",
        {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
        89
        }, {
        "Moscow",
        "Russia",
        {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
        89
        }, {
        "Moscow",
        "Toulouse",
        {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
        89
        }, {
        "Moscow",
        "Russia",
        {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
        31
        },
    }) << std::endl;
}