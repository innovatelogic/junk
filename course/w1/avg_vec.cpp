#include <iostream>
#include <vector>
#include <numeric>

int main()
{
    int n;
    std::cin >> n;

    std::vector<int> v(n);

    for (int i = 0; i < n; ++i){
        std::cin >> v[i];
    }

    int sum = std::accumulate(begin(v), end(v), 0);
    float avg = sum / n;

    int cout_up_avg = 0;
    std::vector<int> indexes;

    for (int i = 0; i < n; ++i)
    {
        if (static_cast<float>(v[i]) > avg)
        {
            ++cout_up_avg;
            indexes.push_back(i);
        }
    }

    std::cout << cout_up_avg << std::endl;
    const size_t size = indexes.size();
    for (int i = 0; i < size; ++i)
    {
        std::cout << indexes[i] << " ";
    }
}