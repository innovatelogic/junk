#pragma once

#include "mathlib.h"

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
                ppmd_point     const p);

        void drawShallowLine(
            const void *   const clientdata,
            pixel **       const pixels,
            int            const cols,
            int            const rows,
            pixval         const maxval,
            ppmd_point     const p0,
            ppmd_point     const p1);

        void
            drawSteepLine(
                const void *   const clientdata,
                pixel **       const pixels,
                int            const cols,
                int            const rows,
                pixval         const maxval,
                ppmd_point     const p0,
                ppmd_point     const p1);

        void
            average_drawproc(pixel **     const pixels,
                int          const cols,
                int          const rows,
                pixval       const maxval,
                int          const col,
                int          const row,
                const void * const clientdata);
    }
}