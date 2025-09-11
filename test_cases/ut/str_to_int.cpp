#include <gtest/gtest.h>

namespace junk
{

int32_t str_to_int(const std::string &str)
{
    int32_t out = 0;

    if (str.empty()){
        return 0;
    }

    bool minus = str[0] == '-' ? true : false;


    // 235
    // 2 * 1;
    const auto len = str.size();
    for (int i = (minus ? 1 : 0); i < len; ++i)
    {
        out *= 10;

        auto digit = str[i] - '0';

        out += digit;
    }

    return (minus) ? -out: out;
}

TEST(Str_to_Int, Test1)
{
    EXPECT_EQ(str_to_int("123"), 123);
    EXPECT_EQ(str_to_int("-123"), -123);
    EXPECT_EQ(str_to_int("0"), 0);
    EXPECT_EQ(str_to_int("-0"), -0);
    EXPECT_EQ(str_to_int(""), -0);
}

}
