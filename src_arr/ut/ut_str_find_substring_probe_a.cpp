#include "arr.h"
#include <gtest/gtest.h>

namespace junk
{
	namespace str_find_substring_probe_a
	{
		TEST(Array, StrFindSubstr_probe_a)
		{
			std::string str("Yabba baba doo");

			EXPECT_EQ(substr<std::string>(str, std::string("baba")), 6);
            EXPECT_EQ(substr<std::string>(str, std::string("doo")), 11);
            EXPECT_EQ(substr<std::string>(str, std::string("das")), -1);
		}
	}
}
