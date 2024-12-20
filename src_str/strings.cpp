#include "strings.h"

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

        //----------------------------------------------------------------------------------------------
        /*void reverse(char *str)
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
        }*/

        //----------------------------------------------------------------------------------------------
        bool is_permutation(const std::string &str1, const std::string &str2)
        {
            bool bResult = true;

            if (str1.size() != str2.size()) {
                return false;
            }

            std::map<char, int> h1;

            for (size_t i = 0; i < str1.size(); ++i)
            {
                if (h1.find(str1[i]) == h1.end()) {
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

        //----------------------------------------------------------------------------------------------
        void replace_str(char **str, char ch, char *with)
        {
            //std::string DEBUG_STR(*str);

            if (*str && with)
            {
                size_t len_with = strlen(with);
                size_t str_len = strlen(*str);

                int count = 0;
                for (int i = 0; i < str_len; ++i) {
                    if ((*str)[i] == ch) {
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

                        delete[] * str;
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
                            for (int j = len_with - 1; j >= 0; j--)
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

        size_t countCompression(const std::vector<junk::string::SymbolCount> &nodes)
        {
            size_t result = nodes.size();

            for (size_t i = 0; i < nodes.size(); ++i)
            {
                int n = nodes[i].n;
                int count = 0;
                while (n)
                {
                    n /= 10;
                    count++;
                }

                result += count;
            }

            return result;
        }

        //----------------------------------------------------------------------------------------------
        std::string compress(const std::string &str)
        {
            std::string result;

            std::vector<junk::string::SymbolCount> nodes;

            for (size_t i = 0; i < str.size(); ++i)
            {
                if (!nodes.empty() && str[i] == nodes[nodes.size() - 1].ch)
                {
                    nodes[nodes.size() - 1].n++;
                }
                else
                {
                    junk::string::SymbolCount node;
                    node.ch = str[i];
                    node.n = 1;
                    nodes.push_back(node);
                }
            }

            const size_t new_size = countCompression(nodes);

            bool bFormString = new_size < str.size();
            if (bFormString)
            {
                result.reserve(new_size);

                for (size_t n = 0; n < nodes.size(); ++n)
                {
                    result += nodes[n].ch + std::to_string(nodes[n].n);
                }
            }

            // form result string
            return bFormString ? result : str;
        }

        //----------------------------------------------------------------------------------------------
        void reverse_str(char *str, int start, int end)
        {
            if (str && (start >= 0 && start < end) && end <= (int)strlen(str))
            {
                while (end > start)
                {
                    std::swap(str[start], str[end]);

                    start++;
                    end--;
                }
            }
        }

        void reverse_words(char *str)
        {
            if (str)
            {
                const int len = strlen(str);

                reverse_str(str, 0, len - 1);

                int index = 0;
                while (index < len)
                {
                    if (str[index] != ' ')
                    {
                        for (int wcount = 0; ; wcount++)
                        {
                            if (index + wcount == len || str[index + wcount] == ' ')
                            {
                                reverse_str(str, index, index + (wcount - 1));
                                index += wcount;
                                break;
                            }
                        }
                    }

                    ++index;
                }
            }
        }
    }
}
