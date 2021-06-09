#include <iostream>
#include <algorithm>

void print_valid_ip(const std::string &str)
{
    const size_t MAX_TOKEN = 3;

    for (size_t i = 0; i < std::min(str.size(), MAX_TOKEN); i++)
    {
        for (size_t j = i + 1; j < std::min(str.size(), i + MAX_TOKEN); j++)
        {
            for (size_t k = j + 1; k < std::min(str.size(), j + MAX_TOKEN); k++)
            {
                std::cout << str.substr(0, i + 1) << " " << str.substr(j, k - j) << " " << str.substr(k) << std::endl; 
            }
        }
    }
}

int main()
{
    print_valid_ip("19216811");
    return 0;
}