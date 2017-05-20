#pragma once

#include "common.h"

namespace junk
{
    namespace cie_conv
    {
        void drawPoint(
                const void *   const clientdata,
                pixel **       const pixels,
                int            const cols,
                int            const rows,
                pixval         const maxval,
                pos_point     const p);

        void drawShallowLine(
            const void *   const clientdata,
            pixel **       const pixels,
            int            const cols,
            int            const rows,
            pixval         const maxval,
            pos_point     const p0,
            pos_point     const p1);

        void drawSteepLine(
                const void *   const clientdata,
                pixel **       const pixels,
                int            const cols,
                int            const rows,
                pixval         const maxval,
                pos_point     const p0,
                pos_point     const p1);
    }
}