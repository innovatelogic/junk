#include <iostream>
#include <string>
#include <set>

std::set<std::string> BuildMapValuesSet(const map<int, string> &m) 
{
    std::set<std::string> out;

    for (auto iter : m)
    {
        out.insert(iter.second);
    }

    return out;
}

int main()
{
    std::set<std::string> cont;

    size_t n;
    std::cin >> n;

    while(n > 0)
    {
        std::string str;
        std::cin >> str;

        cont.insert(str);
        --n;
    }

    std::cout << cont.size() << std::endl;

    return 0;
}