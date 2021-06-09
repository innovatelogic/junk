#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

void foreach_path(const std::vector<std::vector<int>> &arrays, 
                  size_t d, 
                  std::vector<std::vector<int>::const_iterator> &out_path,
                  const std::function<void(std::vector<std::vector<int>::const_iterator>&)> &callback_path)
{
    if (d == arrays.size())
    {
        callback_path(out_path);
        return;
    }

    int n = 0;
    for (auto i : arrays[d])
    {
        out_path[d] = arrays[d].begin() + n++;
        foreach_path(arrays, d + 1, out_path, callback_path);
    }
}

std::pair<int, int> min_max(std::vector<std::vector<int>::const_iterator> &arr)
{
    std::pair<int, int> out;

    if (arr.size() == 1)
    {
        out.first = out.second = *arr[0];
    }
    else if (arr.size() == 2)
    {
        out.first = std::min(*arr[0], *arr[1]);
        out.second = std::max(*arr[0], *arr[1]);
    }
    else
    {
        out.first = *arr[0];
        out.second = *arr[arr.size() - 1];
        for (int i = 0; i < arr.size() - 1; i++)
        {
            out.first = std::min(out.first, *arr[i + 1]);
            out.second = std::max(out.second, *arr[i]);
        }
    }
    return out;
}

std::vector<int> arrays_min_intersection(const std::vector<std::vector<int>> &arrays)
{
    int min_path = std::numeric_limits<int>::max();

    std::vector<std::vector<int>::const_iterator> path_min;
    std::vector<std::vector<int>::const_iterator> path(arrays.size());

    foreach_path(arrays, 0, path, [&](std::vector<std::vector<int>::const_iterator> &path)
    {
        std::pair<int, int> dist = min_max(path);

        //std::cout << "--------------" << std::endl;
        //for (auto p : path){
        //    std::cout << *p << " ";
        //}

        

        int scalar = dist.second - dist.first;

        //std::cout << " | " << scalar;

        if (scalar < min_path){
            path_min = path;
            min_path = scalar;
            //std::cout << " * "; 
        }

        //std::cout << std::endl;
    });

    std::vector<int> out;
    for (auto p : path_min)
    {
        out.push_back(*p);
    }
    return out;
}


int main()
{
    std::vector<std::vector<int>> arr = {
      {5, 10, 15},
      {3, 6, 9, 12, 15},
      {8, 16, 24}  
    };

    auto out = arrays_min_intersection(arr);

    for (auto i : out)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}