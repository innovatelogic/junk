#include <iostream>
#include <string>
#include <set>
#include <map>


bool is_synonim(const std::map<std::string,  std::set<std::string>> &cont, const std::string &a, const std::string &b)
{
    bool result = false;

    auto iter_find = cont.find(a);
    if (iter_find != cont.end())
    {
        result = iter_find->second.count(b) > 0;
    }

    if (!result)
    {
        iter_find = cont.find(b);
        if (iter_find != cont.end())
        {
            result = iter_find->second.count(a) > 0;
        }
    }
    return result;
}

int main()
{
    std::map<std::string,  std::set<std::string>> cont;

    size_t n;
    std::cin >> n;

    while (n > 0)
    {
        std::string command;
        std::cin >> command;

        if (command == "ADD")
        {
            std::string a, b;
            std::cin >> a >> b;

            cont[a].insert(b);
            cont[b].insert(a);
        }
        else if (command == "COUNT")
        {
            std::string a;
            std::cin >> a;

            size_t count = 0;
            auto iter_find = cont.find(a);
            if (iter_find != cont.end()){
                count = iter_find->second.size();
            }
            std::cout << count << std::endl;
        }
        else if (command == "CHECK")
        {
            std::string a, b;
            std::cin >> a >> b;

            std::cout << (is_synonim(cont, a, b) ? "YES" : "NO") << std::endl;
        }
        --n;
    }

    return 0;
}