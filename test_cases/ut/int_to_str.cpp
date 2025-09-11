#include <gtest/gtest.h>
#include <string>


namespace junk
{

std::string int_to_str(int32_t val, int base = 10)
{
    std::string out;

    bool minus = false;
    if (val < 0){
        minus = true;
        val *= -1;
    }



    // 123 % 10 = 3
    // 12 % 10  = 2
    // 1 % 10   = 1

    std::cout << "val: " << val << std::endl;

    do
    {
        out = "0123456789ABCDEF"[val % base] + out;
        val /= base;
    } while(val);

    if (minus){
        out = "-" + out;
    }

    return out;
}

TEST(Int_to_Str, Test1)
{
    {
        EXPECT_EQ(int_to_str(123), "123");
        EXPECT_EQ(int_to_str(-123), "-123");
        EXPECT_EQ(int_to_str(0), "0");
    }
}

}