#include "defexport.h"

#include <string>
#include <math.h>

namespace junk
{
    namespace numbers
    {
        JUNK_EXPORT int str_to_int(const std::string &str, int base)
        {
            int out = 0;

            int n = 0;
            for (int i = str.size() - 1; i >= 0; --i)
            {
                char ch = str[i];

                int k = 0;

                if (ch == 'F' || ch == 'f') {
                    k = 15;
                }
                else if (ch == 'E' || ch == 'e') {
                    k = 14;
                }
                else if (ch == 'D' || ch == 'd') {
                    k = 13;
                }
                else if (ch == 'C' || ch == 'c') {
                    k = 12;
                }
                else if (ch == 'B' || ch == 'b') {
                    k = 11;
                }
                else if (ch == 'A' || ch == 'a') {
                    k = 10;
                }
                else
                {
                    k = ch - (char)'0';
                }

                out += k * (int)std::pow((double)base, n);

                n++;
            }

            return out;
        }

        JUNK_EXPORT bool compare_hex_bin(const std::string &hex, const std::string &bin)
        {
            int val_hex = str_to_int(hex, 16);
            int val_bin = str_to_int(bin, 2);

            return val_bin == val_hex;
        }
    }
}