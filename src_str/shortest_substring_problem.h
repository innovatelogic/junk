#pragma once
#include <string>

namespace junk
{
    namespace shortest_substring_problem
    {
        template<typename>
        std::string get_string_overlap(const std::string &a, const std::string &b)
        {
            if (a.find(b) != std::string::npos) {
                return a;
            }

            std::string out;

            for (size_t i = 0; i < a.size() && out.empty(); i++)
            {
                std::string sub_b = b.substr(0, a.size() - i);
                std::string sub_a = a.substr(i);

                if (sub_b == sub_a)
                {
                    out = a + b.substr(sub_b.size());
                    break;
                }
            }
            return out.empty() ? a + b : out;
        }
    }
}