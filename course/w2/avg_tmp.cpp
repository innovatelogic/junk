#include <iostream>
#include <vector>
#include <cstdint>

// cl /EHsc mycode.cpp

int main()
{
    size_t n = 0;
    std::cin >> n;

    int64_t sum = 0;

    if (n > 0)
    {
        std::vector<int> t(n);
        for (size_t i = 0; i < n; ++i){
            std::cin >> t[i];
            sum += t[i];
        }

        int64_t avg = sum / static_cast<int64_t>(n);

        std::vector<size_t> gr;
        for (size_t i = 0; i < n; ++i)
        {
            if (t[i] > avg)
            {
                gr.push_back(i);
                //std::cout << "insert: " << i << std::endl;
            }
        }

        std::cout << gr.size() << std::endl;
        for (auto i : gr)
        {
            std::cout << i << ' ';
        }
    }

   




    return 0;
}