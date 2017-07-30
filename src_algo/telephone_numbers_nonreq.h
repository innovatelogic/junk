#pragma once
#include <string>
#include <assert.h>
#include <vector>

namespace junk
{
    namespace telephone_numbers_nonreq
    {
        class TelNumber
        {
        public:
            TelNumber(const std::string &str)
                : m_number(str)
            {
                generate();
            }

            void generate()
            {
                std::string result;
                for (size_t n = 0; n < m_number.size(); n++)
                {
                    result += GetCodeChar(m_number[n], 0);
                }

                for (;;)
                {
                    m_combinations.push_back(result);

                    for (int i = m_number.size() - 1; i >= -1; --i)
                    {
                        if (i == -1) {
                            return;
                        }

                        if (GetCodeChar(m_number[i], 2) == result[i] ||
                            m_number[i] == '0' || m_number['1'] == '1')
                        {
                            result[i] = GetCodeChar(m_number[i], 0);
                        }
                        else if (GetCodeChar(m_number[i], 0) == result[i])
                        {
                            result = GetCodeChar(m_number[i], 1);
                            break;
                        }
                        else if (GetCodeChar(m_number[i], 1) == result[i])
                        {
                            result = GetCodeChar(m_number[i], 2);
                            break;
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
            std::vector<std::string> m_combinations;
        };
    }
}
