#pragma once

#include "defexport.h"
#include <string>
#include <vector>

namespace junk
{
    namespace permutate_str
    {
        class JUNK_EXPORT Permutate
        {
        public:
            Permutate(const std::string &str, std::vector<std::string> &out)
                : m_flags(new std::vector<bool>(str.length(), false))
                , m_out(new std::string())
                , m_out_vec(&out)
            {
                PermutateImpl(str);
            }

            ~Permutate()
            {
                delete m_flags;
                delete m_out;
            }

        private:
            void PermutateImpl(const std::string &str)
            {
                if (m_out->length() == str.length())
                {
                    m_out_vec->push_back(*m_out);
                    return;
                }

                for (size_t i = 0; i < str.length(); ++i)
                {
                    if ((*m_flags)[i]) {
                        continue;
                    }

                    (*m_flags)[i] = true;
                    m_out->push_back(str[i]);

                    PermutateImpl(str);

                    m_out->pop_back();

                    (*m_flags)[i] = false;
                }
            }

        private:
            std::vector<bool> *m_flags;

            std::string *m_out;

            std::vector<std::string> *m_out_vec;
        };
    }

}