#pragma once
#include <string>

namespace junk
{
    namespace string_subsequences_probe_a
    {
        class StrSubsequences
        {
        public:
            StrSubsequences(std::string &str)
                : m_str(str) {}

            int Sum()
            {
                return SumImpl(m_str, 0, 0);
            }

        protected:
            int SumImpl(const std::string &in, size_t pos, int sum)
            {
                for (size_t i = pos; i < in.size(); i++)
                {
                    m_str_stack.push_back(in[i]);

                    sum = SumImpl(m_str, i + 1, sum + std::stoi(m_str_stack));

                    m_str_stack.pop_back();
                }
                return sum;
            }

        private:
            std::string m_str;
            std::string m_str_stack;
        };
    }
}