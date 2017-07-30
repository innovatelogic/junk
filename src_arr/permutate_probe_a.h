#pragma once

#include <string>
#include <vector>

namespace junk
{
    namespace permutations_probe_a
    {
        class Permutator
        {
        public:
            Permutator(const std::string &str)
                : m_str(str)
                , m_flags(str.size(), false)
            {}

            std::vector<std::string>& out() { return m_out; }

            void permutate()
            {
                m_out.clear();
                permutate_impl();
            }

            void permutate_impl()
            {
                if (m_buffer.size() == m_str.size()) {
                    m_out.push_back(m_buffer);
                    return;
                }

                for (size_t i = 0; i < m_str.size(); i++)
                {
                    if (m_flags[i]) {
                        continue;
                    }

                    m_flags[i] = true;
                    m_buffer.push_back(m_str[i]);

                    permutate_impl();

                    m_flags[i] = false;
                    m_buffer.pop_back();
                }
            }

        private:
            std::string m_str;
            std::string m_buffer;
            std::vector<std::string> m_out;
            std::vector<bool> m_flags;
        };
    }
}