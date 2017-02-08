#pragma once
#include "defexport.h"
#include <stack>

namespace junk
{
    namespace hanoi_tower
    {
        class JUNK_EXPORT Tower
        {
        public:
            Tower(int index)
                : m_index(index)
                , m_discs(new std::stack<int>())
            {}

            ~Tower()
            {
                delete m_discs;
            }

            int index() const { return m_index; }

            void add(int d)
            {
                if (!m_discs->empty() && m_discs->top() < d)
                {
                    throw;
                }
                
                m_discs->push(d);
            }

            int top() const { return m_discs->top(); }

            void pop()
            {
                m_discs->pop();
            }

        protected:
        private:
            std::stack<int> *m_discs;
            int m_index;
        };

        JUNK_EXPORT void MoveTopTo(Tower &from, Tower &to);
        JUNK_EXPORT void MoveDiscs(int n, Tower &tower1, Tower &tower2, Tower &tower3);
    }
}