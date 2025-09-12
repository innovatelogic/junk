#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <unordered_map>

namespace junk
{

size_t partitioning(std::vector<int> &arr, size_t partition_idx)
{
    if (partition_idx >= arr.size()){
        return 0;
    }

    auto pivot = arr[partition_idx];
    size_t smaller = 0;
    size_t equal = 0;
    size_t larger = arr.size();

    // Keep the following invariants:
    // bottom group: [0, smaller - 1] (Smaller than pivot)
    // middle group: [smaller, equal - 1] (Equal to pivot)
    // unclassified group: [equal, larger - 1]
    // top group: [larger, arr.size() - 1] - (Larger than pivot)

    bool first_eq_hit = true;

    while (equal < larger)
    {
        // arr[equal] - top unclassified element
        if (arr[equal] < pivot) 
        {
            std::swap(arr[smaller++], arr[equal++]);
        }
        else if (arr[equal] == pivot)
        {
            ++equal;
        }
        else // arr[equal] > pivot
        {
            std::swap(arr[equal], arr[--larger]);
        }
    }

    return smaller;
}

bool validate_partitioning(const std::vector<int> &arr, const std::vector<int> &orig, size_t partition_index)
{
    
    std::unordered_map<int, int> hash_key_count_orig;
    std::unordered_map<int, int> hash_key_count;

    if (orig.size() != arr.size() || partition_index >= arr.size()){
        return false;
    }

    for (auto v : orig){
        auto [it, inserted] = hash_key_count_orig.try_emplace(v, 1);

        if (!inserted){
            it->second++;
        }
    }

    for (auto v : arr){
        auto [it, inserted] = hash_key_count.try_emplace(v, 1);

        if (!inserted){
            it->second++;
        }
    }

    if (hash_key_count_orig != hash_key_count){
        return false;
    }

    for (int i = 0; i < partition_index; i++)
    {
        if (arr[i] > arr[partition_index]){
            return false;
        }
    }


    for (int i = partition_index; i < arr.size(); ++i){
        if (arr[i] < arr[partition_index]){
            return false;
        }
    }

    return true;
}

TEST(Partitioning, Test1)
{
    /*{
        std::vector<int> in{0, 1, 2, 0, 2, 1, 1};

        auto orig = in;
        auto orig_pivot = 3;
        auto new_pivot = partitioning(in, orig_pivot);

        EXPECT_EQ(orig[orig_pivot], in[new_pivot]);
        EXPECT_TRUE(validate_partitioning(in, orig, new_pivot));
    }*/


    {
        std::vector<int> in{0, 1, 2, 0, 2, 1, 1};

        auto orig = in;
        auto orig_pivot = 2;
        auto new_pivot = partitioning(in, orig_pivot);

        for (auto v : in){
            std::cout << v << ",";
        }
        std::cout << "\n";

        EXPECT_EQ(orig[orig_pivot], in[new_pivot]);
        EXPECT_TRUE(validate_partitioning(in, orig, new_pivot));
    }

}

}