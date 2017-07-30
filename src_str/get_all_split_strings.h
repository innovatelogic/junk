#pragma once

#include <string>
#include <vector>
#include <stdint.h>
#include <limits.h>
#include <math.h>

namespace junk
{
    namespace get_all_split_strings
    {
        class PartitioningString
        {
        public:
            PartitioningString(const std::string &str)
                : m_str(str)
                , m_mask(0)
            {}

            bool generate()
            {
                if (m_str.size() > sizeof(uint64_t) * CHAR_BIT) {
                    return false;
                }

                uint64_t max_variants = static_cast<uint64_t>(powl(2, m_str.size()) / 2);

                m_mask = 0;
                while (m_mask <= max_variants)
                {
                    m_results.push_back(split(m_mask, m_str));
                    m_mask++;
                }
                return true;
            }

            const std::vector<std::vector<std::string> >& result() const { return m_results; }

            /*int sum(std::vector<std::string> &partition)
            {
                char arr[3] = { '+', '-', ' ' };

                for (size_t i = 0; i < partition.size(); ++i)
                {
                    for (size_t  
                }

                    return result;
            }*/

        private:
            static std::vector<std::string> split(uint64_t mask, const std::string &str)
            {
                std::vector<std::string> out(1, "");

                uint64_t curr = 1;
                uint64_t prev = 1;

                for (size_t index = 0; index < str.size(); ++index)
                {
                    // check sequence changed
                    if (curr > 1 && (mask & curr) != ((mask & prev) << 1)) {
                        out.push_back(std::string());
                    }

                    out[out.size() - 1] += str.at(index);

                    prev = curr;

                    curr = curr << 1;
                }

                return out;
            }

        private:
            std::string m_str;
            uint64_t m_mask;

            std::vector<std::vector<std::string> > m_results;
        };
    }
}