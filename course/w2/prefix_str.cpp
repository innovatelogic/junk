#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
/*
struct cmp {
    bool operator()( const std::string &s, char c ) const { return s.front() < c; }
    bool operator()( char c, const std::string &s ) const { return s.front() < c; }
};
*/

auto get_char(char c)               { return c; }
auto get_char(const std::string &s) { return s.front(); }
auto cmp = [](auto const& l, auto const& r) { return get_char(l) < get_char(r); };

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix)
{
    std::pair<RandomIt, RandomIt> out = std::equal_range(range_begin, range_end, prefix, 
       cmp);

    return out;
}

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith2(
    RandomIt range_begin, RandomIt range_end, char prefix) {
      
    // Все строки, начинающиеся с '<prefix>', больше или равны строке "<prefix>"
    auto left = lower_bound(range_begin, range_end, string(1, prefix));

    // Составим следующий в алфавите символ.
    // Не страшно, если prefix = 'z':
    // в этом случае мы получим следующий за 'z' символ в таблице символов
    char next_prefix = static_cast<char>(prefix + 1);

    // Строка "<next_prefix>" в рамках буквенных строк
    // является точной верхней гранью
    // множества строк, начнающихся с '<prefix>'
    auto right = lower_bound(range_begin, range_end, string(1, next_prefix));

    return {left, right};
}

int main()
{
    const std::vector<std::string> sorted_strings = {"moscow", "murmansk", "vologda"};

    const auto m_result = FindStartsWith(std::begin(sorted_strings), std::end(sorted_strings), 'm');
    for (auto it = m_result.first; it != m_result.second; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    const auto p_result =
        FindStartsWith(std::begin(sorted_strings), std::end(sorted_strings), 'p');
    std::cout << (p_result.first - std::begin(sorted_strings)) << " " <<
        (p_result.second - std::begin(sorted_strings)) << std::endl;

    const auto z_result =
        FindStartsWith(std::begin(sorted_strings), std::end(sorted_strings), 'z');
    std::cout << (z_result.first - std::begin(sorted_strings)) << " " <<
        (z_result.second - std::begin(sorted_strings)) << std::endl;

    return 0;
}