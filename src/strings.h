#include <string>
#include <stdio.h>
#include <map>

namespace junk
{
    namespace string
    {
        void rotate_right(char *str)
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
        }

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

        bool is_permutation(const std::string &str1, const std::string &str2)
        {
            bool bResult = true;

            if (str1.size() != str2.size()) {
                return false;
            }

            std::map<char, int> h1;

            for (size_t i = 0; i < str1.size(); ++i)
            {
                if (h1.find(str1[i]) == h1.end()){
                    h1[str1[i]] = 0;
                }
                h1[str1[i]] += 1;
            }

            for (size_t i = 0; i < str2.size(); ++i)
            {
                if (h1.find(str2[i]) == h1.end()) {
                    bResult = false;
                    break;
                }

                if (--h1[str2[i]] < 0) {
                    bResult = false;
                    break;
                }
            }
            return bResult;
        }
    }
}