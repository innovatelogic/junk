#pragma once

#include <stdlib.h>
#include <vector>
#include <utility>

namespace junk
{
    namespace array_frequency_rand
    {

        /*                 
                                *
                        *       *
                        *       *
                *       *       *
            ______________________
                0   1   2   3   4
            S* = 8
            k-prob = 1/8 -> 1.25

            seq:
            [0; .125), [X], [.125; .5), [X], [.5; 1.)
        */
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
                    float rnd = get_rand(); // 0..1

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

            float get_rand() const { return (float)rand() / (float)(RAND_MAX + 1); } // from [0..1.f)

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


