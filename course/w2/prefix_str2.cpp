#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>


template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const std::string &prefix)
{
    return std::equal_range(range_begin, range_end, prefix,
                            [&prefix](const std::string& a, const std::string& b)
                            {
                                size_t len = prefix.length();
                                return a.compare(0, len, b.substr(0, len)) < 0;
                            });
}

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith2(
	RandomIt range_begin, RandomIt range_end, string prefix) {
	
    // Все строки, начинающиеся с prefix, больше или равны строке "<prefix>"
    auto left = lower_bound(range_begin, range_end, prefix);

    // Составим строку, которая в рамках буквенных строк является
    // точной верхней гранью множества строк, начинающихся с prefix
    string upper_bound = prefix;
    ++upper_bound[upper_bound.size() - 1];

    // Первое встреченное слово, не меньшее upper_bound,
    // обязательно является концом полуинтервала
    auto right = lower_bound(range_begin, range_end, upper_bound);

    return {left, right};
}

int main()
{
   // std::cout << std::boolalpha << ("n" < "moscow") << '\n';

    const std::vector<std::string> sorted_strings = {"moscow", "motovilikha", "murmansk"};

    const auto mo_result = FindStartsWith(std::begin(sorted_strings), std::end(sorted_strings), "mo");
    for (auto it = mo_result.first; it != mo_result.second; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    //std::cout << (mo_result.first - begin(sorted_strings)) << " " <<
    //    (mo_result.second - begin(sorted_strings)) << std::endl;

    const auto mt_result = FindStartsWith(begin(sorted_strings), std::end(sorted_strings), "mt");
    std::cout << (mt_result.first - begin(sorted_strings)) << " " <<
        (mt_result.second - begin(sorted_strings)) << std::endl;

    const auto na_result = FindStartsWith(std::begin(sorted_strings), std::end(sorted_strings), "na");
    std::cout << (na_result.first - std::begin(sorted_strings)) << " " << 
                 (na_result.second - std::begin(sorted_strings)) << std::endl;
  
  return 0;
}