#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

bool isValidChunk(const std::string &chunk)
{
    if (chunk.size() > 3){
        return false;
    }

    unsigned int i = std::atoi(chunk.c_str());
    if (i > 255)
    {
        return false;
    }

    return true;
}

void print_valid_ip(const std::string &str)
{
    const size_t MAX_IP_CHUNK = 3;

    const size_t len = str.size();

    for (size_t i = 0; i < std::min(len, MAX_IP_CHUNK); ++i)
    {
        for (size_t j = i + 1; j < std::min(len, i + MAX_IP_CHUNK); ++j)
        {
            for (size_t k = j + 1; k < std::min(len, j + MAX_IP_CHUNK); ++k)
            {
                std::string ch0 = str.substr(0, i + 1);
                std::string ch1 = str.substr(j, k - j);
                std::string ch2 = str.substr(k);

                if (isValidChunk(ch0) && isValidChunk(ch1) && isValidChunk(ch2)) {
                     std::cout << ch0 << "." << ch1 << "." << ch2 << std::endl;
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