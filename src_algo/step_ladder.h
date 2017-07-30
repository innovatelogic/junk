#pragma once

namespace junk
{
    namespace step_ladder
    {
        // 1 - 3 steps
        template<typename T>
        int countSteppingVariantsReq(int left)
        {
            if (left < 0) {
                return 0; // not a variant
            }
            
            if (left == 0) {
                return 1; // basic
            }

            return countSteppingVariantsReq<T>(left - 1) +
                countSteppingVariantsReq<T>(left - 2) +
                countSteppingVariantsReq<T>(left - 3);
        }

        template<typename T>
        int countSteppingVariantsReq(int left, int m_step)
        {
            if (left == 0) {
                return 1; // basic 
            }

            int count = 0;
            for (int i = 1; i <= m_step && (left - i) >= 0; i++)
            {
                count += countSteppingVariantsReq<T>(left - i, m_step);
            }
            return count;
        }
    }
}