
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
        struct JUNK_EXPORT SymbolCount
        {
            char ch;
            size_t n;
        };

        JUNK_EXPORT void rotate_right(char *str);
         
        JUNK_EXPORT void reverse(char *str);
        JUNK_EXPORT bool is_permutation(const std::string &str1, const std::string &str2);
        JUNK_EXPORT void replace_str(char **str, char ch, char *with);

        JUNK_EXPORT size_t countCompression(const std::vector<junk::string::SymbolCount> &nodes);

        JUNK_EXPORT std::string compress(const std::string &str);
        JUNK_EXPORT void reverse_str(char *str, int start, int end);
        JUNK_EXPORT void reverse_words(char *str);
       
    }
}