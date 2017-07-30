#pragma once

namespace array
{
    namespace is_palindrome
    {
        template<typename T>
        bool isPalindrome(const T &str)
        {
            if (str.empty()) {
                return false;
            }

            int i = 0;
            int j = str.size() - 1;

            while (i < j)
            {
                if (str[i] != str[j]) {
                    break;
                }
                i++;
                j--;
            }
            return !(i < j);
        }
    }
}