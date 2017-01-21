#include "is_unique_chars_in_string.h"
#include <string>
#include <stdio.h>

namespace junk
{
    namespace string
    {
        // ascii symbols only
        bool is_unique_chars_in_string(const std::string &str)
        {
            bool bResult = true;

            const int ASCII_SIZE = 256;

            if (str.size() > 256) {
                return bResult;
            }

            bool *flags = new bool[ASCII_SIZE];

            memset(flags, false, ASCII_SIZE);

            for (size_t i = 0; i < str.size(); ++i)
            {
                char ch = str[i];

                if (flags[ch]) {
                    bResult = false;
                    break;
                }

                flags[ch] = true;
            }

            delete[] flags;

            return bResult;
        }

        bool is_unique_low_letters_in_string(const std::string &str)
        {
            bool bResult = true;

            const int ALPHABET_CAPECITY = 26;

            if (str.size() > ALPHABET_CAPECITY) {
                return false;
            }

            int mask = 0; // means 32 bit

            for (size_t i = 0; i < str.size(); ++i)
            {
                char ch = str[i];

                int index = ch - char('a');

                if (mask & 1 << index) {
                    bResult = false;
                    break;
                }
                mask |= 1 << index;
            }

            return bResult;
        }

        /*void rotate_right(char *str)
        {
            if (str)
            {
                int len = strlen(str);
                if (len > 1)
                {
                    char tmp = str[len - 1];

                    for (int i = len - 1; i >= 1; --i)
                    {
                        str[i] = str[i - 1];
                    }
                    str[0] = tmp;
                }
            }
        }*/

        void reverse(char *str)
        {
            if (str)
            {
                int len = strlen(str);
                if (len > 1)
                {
                    char *lhs = &str[0];
                    char *rhs = &str[len - 1];

                    while (lhs < rhs)
                    {
                        std::swap(*rhs, *lhs);
                        lhs++;
                        rhs--;
                    }
                }
            }
        }
    }
}
