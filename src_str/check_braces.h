#pragma once

#include <stack>
#include <string>
#include <algorithm>
#include <vector>

namespace junk
{
    namespace check_string_braces
    {
        class BracesCheck
        {
        public:
            BracesCheck(const std::string &str)
                : m_str(str)
                , m_opening{ '(', '[', '{', '<' }
                , m_closing{ ')', ']', '}', '>' }
            {}

            bool check()
            {
                std::stack<char> s;

                for (size_t i = 0; i < m_str.size(); i++)
                {
                    if (std::find(m_opening.begin(), m_opening.end(), m_str[i]) != m_opening.end())
                    {
                        s.push(m_str[i]);
                    }
                    else if (std::find(m_closing.begin(), m_closing.end(), m_str[i]) != m_closing.end())
                    {
                        if (s.empty() || !isPair(s.top(), m_str[i])) {
                            return false;
                        }

                        s.pop();
                    }
                }
                return s.empty();
            }

            bool isPair(char opening, char closing)
            {
                return (opening == m_opening[0] && closing == m_closing[0]) ||
                    (opening == m_opening[1] && closing == m_closing[1]) ||
                    (opening == m_opening[2] && closing == m_closing[2]) ||
                    (opening == m_opening[3] && closing == m_closing[3]);
            }

        public:
            std::string m_str;
            const std::vector<char> m_opening;
            const std::vector<char> m_closing;
        };
    }
}