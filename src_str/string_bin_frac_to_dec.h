#pragma once

#include <string>

namespace junk
{
    namespace string_bin_frac_to_dec
    {
        template<typename T>
        float str_bin_frac_to_dec(const std::string &str)
        {
            float main_n = 0.f;
            float frac_n = 0.f;

            if (!str.empty())
            {
                bool b_frac = true;

                size_t radix = str.find('.');
                if (radix == std::string::npos) {
                    b_frac = false;
                }

                int pow_two = 1;
                for (int i = b_frac ? (radix - 1) : str.size() - 1; i >= 0; --i)
                {
                    main_n += (str[i] - '0') * pow_two;
                    pow_two *= 2;
                }

                if (b_frac)
                {
                    pow_two = 2;
                    for (size_t i = radix + 1; i < str.size(); ++i)
                    {
                        frac_n += (str[i] - '0') * (1.f / (pow_two));
                        pow_two *= 2;
                    }
                }
            }
            return main_n + frac_n;
        }
    }
}