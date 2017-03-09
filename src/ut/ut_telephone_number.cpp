#include "junk.h"
#include <gtest/gtest.h>
namespace junk
{ 
    namespace telephone_numbers
    {
        TEST(Combinatorics, TelephoneNumbers)
        {
            TelNumber tel(std::string("0730591731"));
        }

        namespace telephone_numbers_nonreq
        {
            TEST(Combinatorics, TelephoneNumbersNonReq)
            {
                TelNumber tel(std::string("0730591731"));
            }
        }
    }
}