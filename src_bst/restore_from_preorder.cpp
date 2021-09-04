#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <string>

template<typename T>
struct node
{
    T data;
    std::unique_ptr<node> lhs;
    std::unique_ptr<node> rhs; 

    void print()
    {
        std::cout << "(" << data << " l:" << (lhs ? std::to_string(lhs->data) : "")
         << " r:" << (rhs ? std::to_string(rhs->data) : "") << ")" << std::endl;

        if (lhs) { lhs->print(); }
        if (rhs) { rhs->print(); }
    }
};

std::unique_ptr<node<int>> restore_from_preorder_impl(const std::vector<int> &array, size_t start, size_t end)
{
    if (start >= end){
        return nullptr;
    }

    auto pivot = std::distance(array.cbegin(),
                                  std::find_if_not(
                                      array.cbegin() + start,
                                      array.cend(),
                                      [&](const int a) { return a <= array[start];}));

    auto lhs = restore_from_preorder_impl(array, start + 1, pivot);
    auto rhs = restore_from_preorder_impl(array, pivot, end);


    return std::make_unique<node<int>>(node<int>{array[start], std::move(lhs), std::move(rhs)});
}

std::unique_ptr<node<int>> restore_from_preorder(const std::vector<int> &array)
{
    return restore_from_preorder_impl(array, 0, array.size());
}


std::unique_ptr<node<int>> restore_from_preorder_impl2(const std::vector<int> &array,
                                                       int lower_bound,
                                                       int upper_bound,
                                                       int *pivot_index)
{

    // {43, 23, 37, 29, 31, 41, 47, 53}
    // L - 43 - U
    //     L - 23 - (U:43)
    //        L - 37 - (U:23) x
    //        (L:23 - 37 - U)

    std::cout << "l:" << lower_bound << " r:" << upper_bound << " idx:" << *pivot_index << std::endl;

    int &root_idx = *pivot_index;

    if (root_idx == array.size()) {
        return nullptr;
    }

    int root = array[root_idx];

    if (root < lower_bound || root > upper_bound){
        return nullptr;
    }

    root_idx++;

    auto lhs = restore_from_preorder_impl2(array, lower_bound, root, pivot_index);
    auto rhs = restore_from_preorder_impl2(array, root, upper_bound, pivot_index);

    return std::make_unique<node<int>>(node<int>{root, std::move(lhs), std::move(rhs)});
}

std::unique_ptr<node<int>> restore_from_preorder_v2(const std::vector<int> &array)
{
    int root_index = 0;

    return restore_from_preorder_impl2(array,
                                        std::numeric_limits<int>::min(), 
                                        std::numeric_limits<int>::max(), &root_index);
}

int main()
{
    std::vector<int> a({43,23,37,29,31,41,47,53});

    auto ptr1 = restore_from_preorder_v2(a);
    ptr1->print();

    auto ptr2 = restore_from_preorder_v2(a);
    ptr2->print();

    
}