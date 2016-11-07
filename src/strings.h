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

        void replace_str(char **str, char ch, char *with)
        {
            //std::string DEBUG_STR(*str);

            if (*str && with)
            {
                int len_with = strlen(with);
                int str_len = strlen(*str);

                int count = 0;
                for (int i = 0; i < str_len; ++i) {
                    if ((*str)[i] == ch){
                        count++;
                    }
                }

                if (count)
                {
                    int diff = len_with - 1;

                    if (diff > 1)
                    {
                        int num_extend = count * diff;
                        char *new_str = new char[str_len + num_extend + 1]; // +1 null terminated

                        strncpy_s(new_str, str_len + num_extend + 1, *str, str_len);

                        //DEBUG_STR.resize(str_len + num_extend + 1);

                        new_str[str_len + num_extend] = char('\0');

                        delete [] *str;
                        *str = new_str;
                    }

                    int n_swap_back = diff * count;

                    for (int i = str_len - 1; i >= 0; --i)
                    {
                        if ((*str)[i] != ch)
                        {
                            (*str)[i + n_swap_back] = (*str)[i];

                            //DEBUG_STR[i + n_swap_back] = DEBUG_STR[i];
                        }
                        else
                        {
                            for (int j = len_with - 1; j >=0; j--)
                            {
                                (*str)[i + n_swap_back - j] = with[len_with - 1 - j];

                                //DEBUG_STR[i + n_swap_back - j] = with[len_with - 1 - j];
                            }

                            n_swap_back -= diff;
                        }
                    }
                }
            }
        }
    }
}