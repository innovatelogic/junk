#include "../str.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace shortest_substring_problem
    {
        TEST(String, Overlap_ShortestSubstringProblem)
        {
            {
                const std::string a("AGATTA");
                const std::string b("GATTACA");

                std::string overlap = get_string_overlap<void>(a, b);

                EXPECT_EQ(overlap, "AGATTACA");
            }

            {
                const std::string a("AGATTA");
                const std::string b("GAT");

                std::string overlap = get_string_overlap<void>(a, b);

                EXPECT_EQ(overlap, "AGATTA");
            }

            {
                const std::string a("AGA");
                const std::string b("TAC");

                std::string overlap = get_string_overlap<void>(a, b);

                EXPECT_EQ(overlap, "AGATAC");
            }
        }
    }
}