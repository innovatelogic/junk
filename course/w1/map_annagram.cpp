#include <iostream>
#include <string>
#include <map>

std::map<char, int> build_annagram(const std::string &w)
{
    std::map<char, int> res;

    for (size_t i = 0; i < w.size(); ++i)
    {
        res[w[i]]++;
    }

    return res;
}

bool is_annagram(const std::string &a, const std::string &b)
{
    return build_annagram(a) == build_annagram(b);
}

int main()
{
    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i)
    {
        std::string a, b;

        std::cin >> a >> b;

        std::cout << (is_annagram(a, b) ? "YES" : "NO") << std::endl;
    }

    return 0;
}