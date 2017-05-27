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

        template<typename>
        std::string shortest_substring(std::vector<std::string> &strings)
        {
            int **array;
            array = new int*[strings.size()];
            for (int i = 0; i < strings.size(); i++){
                *array[i] = new int[strings.size()];
            }

            for (int i = 0; i < strings.size(); i++)
            {
                for (int j = 0; j < strings.size(); j++)
                {
                    array[i][j] = (i != j) ? get_string_overlap(strings[i], strings[j]) : 0;
                }
            }


            for (int i = 0; i < strings.size(); i++) {
                delete [] *array[i];
            }
            delete[] array;
        }

    }
}