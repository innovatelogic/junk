#pragma once
#include <string>
#include <assert.h>
#include <vector>

namespace junk
{
    namespace telephone_numbers
    {
        class TelNumber
        {
        public:
            explicit TelNumber(const std::string &number)
                : m_number(number)
            {
                generate(0);
            }

            void generate(size_t n)
            {
                if (m_buffer.size() == m_number.size())
                {
                    m_combinations.push_back(m_buffer);
                    return;
                }

                for (size_t i = n; i < m_number.size(); ++i)
                {
                    for (int j = 0; j < 3; ++j)
                    {
                        m_buffer.push_back(GetCodeChar(m_number[i], j));

                        generate(i + 1);

                        m_buffer.pop_back();

                        if (m_number[i] == '0' || m_number[i] == '1') {
                            return;
                        }
                    }
                }
            }

            static char GetCodeChar(const char c, size_t n)
            {
                char out = '_';

                switch (c)
                {
                case '0': { out = '0'; } break;
                case '1': { out = '1'; } break;
                case '2': { out = "ABC"[n]; } break;
                case '3': { out = "DEF"[n]; } break;
                case '4': { out = "GHI"[n]; } break;
                case '5': { out = "JKL"[n]; } break;
                case '6': { out = "MNO"[n]; } break;
                case '7': { out = "PQR"[n]; } break;
                case '8': { out = "TUV"[n]; } break;
                case '9': { out = "WXY"[n]; } break;
                default: {
                    assert(false);
                }break;
                }
                return out;
            }

        private:
            std::string m_number;
            std::string m_buffer;
            std::vector<std::string> m_combinations;
        };
    }
}