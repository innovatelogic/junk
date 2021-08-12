#include <iostream>
#include <assert.h>

#define EXPECT_TRUE(X, Y) assert((X) == Y)

int main()
{
    //  00110 - 6
    //  00100 - 4
    //  00100

    EXPECT_TRUE( (6 & 4), 4);
    EXPECT_TRUE( (2 & 4), 0);
    EXPECT_TRUE( (9 & 9), 9);

    EXPECT_TRUE( (16 | 8), 24); // 24   // 10000
                                        // 01000   
    // 52
    EXPECT_TRUE( (32 | 16 | 4), 52); 

    // 55
    EXPECT_TRUE( (32 | 16 | 7), 55); 

    EXPECT_TRUE( (1 | 2), 3);

    EXPECT_TRUE( 8 >> 1, 4);

    // 1010
    EXPECT_TRUE( 10 << 1, 20);
    

}