#include <iostream>
#include <algorithm>
#include <string>

bool isValidIP(const std::string &v)
{
    if (v.empty()){
        return false;
    }
    if (v.size() > 3){
        return false;
    }

    if (std::atoi(v.c_str()) > 255)
    {
        return false;
    }
    return true;
}

void print_valid_ip(const std::string &str)
{
    std::cout << "[ " << str << " ]" << std::endl;

    const size_t MAX_CHUNK = 3;
    const size_t len = str.size();

    for (size_t i = 0; i < std::min(len, MAX_CHUNK); ++i)
    {
        for (size_t j = i + 1; j < std::min(len, (i + 1) + MAX_CHUNK); ++j)
        {
            for (size_t k = j + 1; k < std::min(len, j + 1 + MAX_CHUNK); ++k)
            {

                if (isValidIP(str.substr(0, i + 1)) &&
                     isValidIP(str.substr((i + 1), j - i)) &&
                     isValidIP(str.substr(j + 1, k - j)) &&
                     isValidIP(str.substr(k + 1))
                    ) 
                    {
                    std::cout << str.substr(0, i + 1) << "."
                              << str.substr((i + 1), j - i) << "." 
                              << str.substr(j + 1, k - j) << "."
                              << str.substr(k + 1) 
                              /*<< " [ " << i << " , " << j << " , " << k << " ]"*/ << std::endl; 
                    }
            }
        }
    }
}



int main()
{
    print_valid_ip("19216811");
    return 0;
}