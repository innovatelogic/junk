#pragma once

namespace junk
{
    namespace cie_conv
    {
        void xyz_to_rgb(const struct colorSystem * const cs,
                double                      const xc,
                double                      const yc,
                double                      const zc,
                double *                    const r,
                double *                    const g,
                double *                    const b);

        void upvp_to_xy(double   const up,
                double   const vp,
                double * const xc,
                double * const yc);


        void computeMonochromeColorLocation(
            double                     const waveLength,
            int                        const pxcols,
            int                        const pxrows,
            int *                      const xP,
            int *                      const yP);

        int constrain_rgb(double * const r,
                double * const g,
                double * const b);

        bool pointsEqual(ppmd_point const a, ppmd_point const b);

        //----------------------------------------------------------------------------------------------
        void findTongue(pixel ** const pixels,
            int      const pxcols,
            int      const row,
            bool *   const presentP,
            int *    const leftEdgeP,
            int *    const rightEdgeP);
    }
}