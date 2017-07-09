#include "hanoi_tower.h"

namespace junk
{
    namespace hanoi_tower
    {
        void MoveTopTo(Tower &from, Tower &to)
        {
            int top = from.top();
            from.pop();
            to.add(top);
        }

        void MoveDiscs(int n, Tower &source, Tower &target, Tower &aux)
        {
            if (n > 0)
            {
                // move n - 1 discs from tower1 to tower2 using tower3 as buffer
                MoveDiscs(n - 1, source, aux, target);

                // move top from tower1 to tower3
                MoveTopTo(source, target);

                // move n - 1 discs from tower2 to tower3 using tower1 as buffer
                MoveDiscs(n - 1, aux, target, source);
            }
        }
    }
}