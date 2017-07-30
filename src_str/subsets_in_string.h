#pragma once
#include <string>
#include <vector>

namespace junk
{
    namespace subsets_in_string
    {
        class StringSubsets
        {
        public:
            explicit StringSubsets(std::string &str)
                : m_str(str)
            {}

        private:
            void permute(std::string soFar, std::string rest)
            {
                //for (int i = 0; i)
            }

            std::string m_str;
            std::vector<std::string> m_combinations;
        };
    }
}

