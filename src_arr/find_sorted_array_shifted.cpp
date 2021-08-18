#include <iostream>
#include <vector>

bool find_sorted_shifted(int val, const int *data, size_t lhs, size_t rhs)
{
    if (lhs > rhs){
        return false;
    }

    std::cout << "lhs : " << lhs << " : " << "rhs : " << rhs << std::endl;

    size_t mid = (lhs + rhs) / 2;

    if (val < data[lhs])
    {
        return find_sorted_shifted(val, data, mid + 1, rhs); // search right
    }
    else if (val > data[rhs])
    {
        return find_sorted_shifted(val, data, lhs, mid - 1); // search left
    }

   /* if (val >= data[lhs] && val < data[mid]) {
        return find_sorted_shifted(val, data, lhs, mid - 1);
    }
    else if (val > data[mid] && val <= data[rhs])
    {
        return find_sorted_shifted(val, data, mid + 1, rhs);
    }*/
    return data[mid] == val || data[lhs] == val || data[rhs] == val;
}


int main()
{
    std::vector<int> arr = {12, 17, 25, 27, 2, 5, 10};

    if (find_sorted_shifted(11, arr.data(), 0, arr.size() - 1)) {
        std::cout << "true" << std::endl;
    }
    else {
        std::cout << "false" << std::endl;
    }

    return 0;
}