#include <gtest/gtest.h>
#include <iostream>

const int num_chars = 26;

bool is_sorted(const std::string&);
char ith_char(int i);
void print_sorted_strings(int remaining, std::string prefix);

void print_sorted_strings(int remaining) {
    print_sorted_strings(remaining, {});
}

// At each level of recursion, the function explores all c characters, leading to a total of c^n strings.
// For each generated string, is_sorted performs a linear scan to verify if the string is in non-decreasing order, which takes O(n) time.
// The overall time complexity is O(c^n * n), where c is the number of characters (26) and n is the length of the string.
void print_sorted_strings(int remaining, std::string prefix)
{
    if (remaining == 0)
    {
        if (is_sorted(prefix)) {
            std::cout << prefix << std::endl;
        }
    } 
    else 
    {
        for (int i = 0; i < num_chars; ++i)
        {
            char c = ith_char(i);
            print_sorted_strings(remaining - 1, prefix + c);
        }
    }
}

char ith_char(int i)
{
    return (char)(((int('a')) + i));
}

// For each generated string, is_sorted performs a linear scan to verify if the string is in non-decreasing order, which takes O(n) time.
bool is_sorted(const std::string& str)
{
    for (int i = 1; i < str.size(); ++i)
    {
        auto prev = str[i - 1];
        auto curr = str[i];

        if (prev > curr){
            return false;
        }
    }
    return true;
}


TEST(PrintSortedStrings, Test1)
{
    print_sorted_strings(2);
    // print_sorted_strings(4);
    // print_sorted_strings(5);
}

