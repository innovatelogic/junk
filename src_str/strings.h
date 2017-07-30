
#pragma once

#include "defexport.h"
#include <string>
#include <stdio.h>
#include <map>
#include <vector>

namespace junk
{
    namespace string
    {
        struct __STR_EXPORT SymbolCount
        {
            char ch;
            size_t n;
        };

        __STR_EXPORT void rotate_right(char *str);
         
        __STR_EXPORT void reverse(char *str);
        __STR_EXPORT bool is_permutation(const std::string &str1, const std::string &str2);
        __STR_EXPORT void replace_str(char **str, char ch, char *with);

        __STR_EXPORT size_t countCompression(const std::vector<junk::string::SymbolCount> &nodes);

        __STR_EXPORT std::string compress(const std::string &str);
        __STR_EXPORT void reverse_str(char *str, int start, int end);
        __STR_EXPORT void reverse_words(char *str);
       
    }
}