#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <locale>

// cl /EHsc mycode.cpp

void A(int n)
{
    std::vector<int> cont(n);

    int k = 0;
    while (n > 0)
    {
        std::cin >> cont[k++];
        --n;
    }

    std::sort(begin(cont), end(cont), [](int lhs, int rhs)
    {
        return std::abs(lhs) < std::abs(rhs);
    });

    for (auto i : cont)
    {
        std::cout << i << ' ';
    }
}

void B(int n)
{
    std::vector<std::string> cont(n);

    int k = 0;
    while (n > 0)
    {
        std::cin >> cont[k];

        ++k;
        --n;
    }

    std::sort(begin(cont), end(cont), [](const auto &lhs, const auto &rhs)
    {
         return lexicographical_compare(
             begin(lhs), end(lhs),
             begin(rhs), end(rhs),
             [](char cl, char cr) { return tolower(cl) < tolower(cr); }
         );
    });

    for (const auto &i : cont)
    {
        std::cout << i << ' ';
    }
}

int main()
{
    size_t n;
    std::cin >> n;

    B(n);
}