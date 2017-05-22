#pragma once 

namespace junk
{
    namespace swap_no_tmp
    {
        /*!
            Swaps two ints without assign tmp variable

            0 -----------------> b <---- diff ------> a

            0 -----------------> a <---- diff ------> b

        */
        template<typename>
        void var_swap_no_tmp(int &a, int &b)
        {
            a = a - b;
            b = b + a;
            a = b - a;
        }
    }
}