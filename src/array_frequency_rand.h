#pragma once

#include <stdlib.h>
#include <vector>
#include <utility>

namespace junk
{
    namespace array_frequency_rand
    {
        template<typename T>
        class freq_random_selector
        {
        public:
            typedef std::vector<std::pair<T, unsigned int>> TVecIn;

            freq_random_selector(const TVecIn &arr) { redistribute_probability(arr); }

            bool get_rand(T &out)
            {
                if (m_keys.size() > 0)
                {
                    float rnd = get_rand();

                    float last = 0.f;
                    for (size_t i = 0; i < m_keys.size(); ++i)
                    {
                        if (rnd >= last && rnd < m_keys[i].second) {
                            out = m_keys[i].first;
                            return true;
                        }
                        last = m_keys[i].second;
                    }
                }
                return false;
            }

            float get_rand() const { return (float)rand() / (float)RAND_MAX; }

        protected:
            void redistribute_probability(const TVecIn &arr)
            {
                m_keys.clear();

                int total_count = 0;
                for (auto &i : arr) {
                    total_count += i.second;
                }

                float k = (total_count > 0) ? 1.f / total_count : 0.f;

                float last = 0.f;
                for (auto &i : arr)
                {
                    float lhs_p = last + i.second * k;
                    m_keys.push_back(std::pair<T, float>(i.first, lhs_p));
                    last = lhs_p;
                }
            }

        private:
            std::vector<std::pair<T, float>> m_keys;
        };
    }
}


