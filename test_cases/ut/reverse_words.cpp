#include <gtest/gtest.h>
#include <string>
#include <iostream>

namespace junk
{

void reverse(std::string &str, size_t start, size_t end)
{
    while (start < end)
    {
        char tmp = str[start];
        str[start] = str[end];
        str[end] = tmp;
        start++;
        end--;
    }
}

void reverse_words(std::string &str)
{
    if (str.empty()){
        return;
    }

    reverse(str, 0, str.size() - 1);

    // Use scanning to detect start word position and end word position
    // invariant
    // symbol array divided by three windows using two pointers pattern
    // (0,  word_start - 1) [word_start,  scan_pos] (scan_pos + 1, n)
    // (0,  word_start - 1) - already processed window
    // [word_start,  scan_pos] - scanning frame, 
    //                           find first non space symbol - write position to word_start
    //                           continue scaning to find end of the word
    //                           reverse[word_start, end_word]
    //                           continue scanning from word end


    // ____aaa___bbb____

    size_t scan_pos = 0;

    while (scan_pos < str.size())
    {
        if (str[++scan_pos] != ' ')
        {
            size_t word_start = scan_pos;

            scan_pos++;

            while (scan_pos < str.size()){

                if (str[scan_pos] == ' '){
                    break;
                }

                ++scan_pos;
            }

            reverse(str, word_start, scan_pos - 1);
        }

    }
}

TEST(ReverseWords, Test)
{
    {
        std::string in{" abc def ghk "};
        std::string eq{" ghk def abc "};
        reverse_words(in);
        EXPECT_EQ(in, eq);
    }

    {
        std::string in{"a b c"};
        std::string eq{"c b a"};
        reverse_words(in);
        EXPECT_EQ(in, eq);
    }

    {
        std::string in{"    "};
        std::string eq{"    "};
        reverse_words(in);
        EXPECT_EQ(in, eq);
    }

    {
        std::string in{""};
        std::string eq{""};
        reverse_words(in);
        EXPECT_EQ(in, eq);
    }
}

}