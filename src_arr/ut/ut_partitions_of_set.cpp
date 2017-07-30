#include "../arr.h"
#include <gtest/gtest.h>
#include <vector>
#include <string>

namespace junk
{
    namespace partitions_of_set
    {
        std::vector<std::vector<std::string>> result;

        std::vector<std::string> track;

        void permute(size_t start_broad, std::vector<std::string> &broad, std::vector<std::string> &low)
        {
            if (start_broad == broad.size())
            {
                result.push_back(track);
                return;
            }

            for (size_t j = 0; j < low.size(); ++j)
            {
                track.push_back(broad[start_broad] + low[j]);

                permute(start_broad + 1, broad, low);

                track.pop_back();
            }
        }
       
        TEST(Combinatorics, PermutationOfSets)
        {
            std::vector<std::string> s = { "a", "b", "c" };
            std::vector<std::string> v = { "1", "2", "3" };

            permute(0, s, v);

            EXPECT_EQ(result.size(), 3 * 3 * 3);
        }
    }
}