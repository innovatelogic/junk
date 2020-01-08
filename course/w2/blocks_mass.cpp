#include <iostream>
#include <vector>
#include <cstdint>

struct block
{
    uint16_t x;
    uint16_t y;
    uint16_t z;

};

int main()
{
    size_t n = 0;
    std::cin >> n;

    int r = 0;
    std::cin >> r;

    uint64_t v = 0u;

    for (size_t i = 0; i < n; ++i)
    {
        uint64_t x, y, z;

        std::cin >> x >> y >> z;

        v += (x * y * z);
    }
        
    std::cout << v * r << std::endl;

    return 0;
}