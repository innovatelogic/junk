
#pragma once

#include <string>
#include <vector>

namespace junk
{
    namespace combinations
    {
        class Combinations
        {
        public:
            Combinations(const std::string &str)
                : m_str(str)
            {
                combine(0);
            }

            void combine(size_t start)
            {
                for (size_t i = start; i < m_str.size(); ++i)
                {
                    out += m_str[i];

                    m_combinations.push_back(out);
                    
                    combine(i + 1);

                    out.pop_back();
                }
            }

        private:
            std::string out;
            std::string m_str;

            std::vector<std::string> m_combinations;
        };

    }
}