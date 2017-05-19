
#include "mathlib.h"
#include "cie_model_helper.h"

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
                double *                    const b) {
            /*----------------------------------------------------------------------------
            Given  an additive tricolor system CS, defined by the CIE x and y
            chromaticities of its three primaries (z is derived  trivially  as
            1-(x+y)),  and  a  desired chromaticity (XC, YC, ZC) in CIE space,
            determine the contribution of each primary in a linear combination
            which   sums  to  the  desired  chromaticity.   If  the  requested
            chromaticity falls outside the  Maxwell  triangle  (color  gamut)
            formed  by the three primaries, one of the r, g, or b weights will
            be negative.

            Caller can use constrain_rgb() to desaturate an outside-gamut
            color to the closest representation within the available
            gamut.
            -----------------------------------------------------------------------------*/
            double xr, yr, zr, xg, yg, zg, xb, yb, zb;
            double xw, yw, zw;
            double rx, ry, rz, gx, gy, gz, bx, by, bz;
            double rw, gw, bw;

            xr = cs->xRed;    yr = cs->yRed;    zr = 1 - (xr + yr);
            xg = cs->xGreen;  yg = cs->yGreen;  zg = 1 - (xg + yg);
            xb = cs->xBlue;   yb = cs->yBlue;   zb = 1 - (xb + yb);

            xw = cs->xWhite;  yw = cs->yWhite;  zw = 1 - (xw + yw);

            /* xyz -> rgb matrix, before scaling to white. */
            rx = yg*zb - yb*zg;  ry = xb*zg - xg*zb;  rz = xg*yb - xb*yg;
            gx = yb*zr - yr*zb;  gy = xr*zb - xb*zr;  gz = xb*yr - xr*yb;
            bx = yr*zg - yg*zr;  by = xg*zr - xr*zg;  bz = xr*yg - xg*yr;

            /* White scaling factors.
            Dividing by yw scales the white luminance to unity, as conventional. */
            rw = (rx*xw + ry*yw + rz*zw) / yw;
            gw = (gx*xw + gy*yw + gz*zw) / yw;
            bw = (bx*xw + by*yw + bz*zw) / yw;

            /* xyz -> rgb matrix, correctly scaled to white. */
            rx = rx / rw;  ry = ry / rw;  rz = rz / rw;
            gx = gx / gw;  gy = gy / gw;  gz = gz / gw;
            bx = bx / bw;  by = by / bw;  bz = bz / bw;

            /* rgb of the desired point */
            *r = rx*xc + ry*yc + rz*zc;
            *g = gx*xc + gy*yc + gz*zc;
            *b = bx*xc + by*yc + bz*zc;
        }

        //----------------------------------------------------------------------------------------------
        void upvp_to_xy(double   const up,
                double   const vp,
                double * const xc,
                double * const yc) {
            /*----------------------------------------------------------------------------
            Given 1976 coordinates u', v', determine 1931 chromaticities x, y
            -----------------------------------------------------------------------------*/
            *xc = 9 * up / (6 * up - 16 * vp + 12);
            *yc = 4 * vp / (6 * up - 16 * vp + 12);
        }

        //----------------------------------------------------------------------------------------------
        void computeMonochromeColorLocation(
            double                     const waveLength,
            int                        const pxcols,
            int                        const pxrows,
            int *                      const xP,
            int *                      const yP) {

            int const ix = (int)((waveLength - 380) / 5);
            double const px = spectral_chromaticity[ix][0];
            double const py = spectral_chromaticity[ix][1];

            *xP = (int)(px * (pxcols - 1));
            *yP = (int)((pxrows - 1) - py * (pxrows - 1));
        }

        void gamma_correct(const struct colorSystem * const cs,
                double *                   const c) 
        {
            /*----------------------------------------------------------------------------
            Transform linear RGB values to nonlinear RGB values.

            Rec. 709 is ITU-R Recommendation BT. 709 (1990)
            ``Basic Parameter Values for the HDTV Standard for the Studio and for
            International Programme Exchange'', formerly CCIR Rec. 709.

            For details see
            http://www.inforamp.net/~poynton/ColorFAQ.html
            http://www.inforamp.net/~poynton/GammaFAQ.html
            -----------------------------------------------------------------------------*/
            double gamma;

            gamma = cs->gamma;

            if (gamma == 0.) {
                /* Rec. 709 gamma correction. */
                double cc = 0.018;
                if (*c < cc) {
                    *c *= (1.099 * pow(cc, 0.45) - 0.099) / cc;
                }
                else {
                    *c = 1.099 * pow(*c, 0.45) - 0.099;
                }
            }
            else {
                /* Nonlinear color = (Linear color)^(1/gamma) */
                *c = pow(*c, 1. / gamma);
            }
        }

        void gamma_correct_rgb(const struct colorSystem * const cs,
                double * const r,
                double * const g,
                double * const b) {
            gamma_correct(cs, r);
            gamma_correct(cs, g);
            gamma_correct(cs, b);
        }

        int
            constrain_rgb(double * const r,
                double * const g,
                double * const b) {
            /*----------------------------------------------------------------------------
            If  the  requested RGB shade contains a negative weight for one of
            the primaries, it lies outside the color  gamut  accessible  from
            the  given  triple  of  primaries.  Desaturate it by adding white,
            equal quantities of R, G, and B, enough to make RGB all positive.
            -----------------------------------------------------------------------------*/
            double w;

            /* Amount of white needed is w = - min(0, *r, *g, *b) */
            w = (0 < *r) ? 0 : *r;
            w = (w < *g) ? w : *g;
            w = (w < *b) ? w : *b;
            w = -w;

            /* Add just enough white to make r, g, b all positive. */
            if (w > 0) {
                *r += w;  *g += w; *b += w;

                return 1;                     /* Color modified to fit RGB gamut */
            }

            return 0;                         /* Color within RGB gamut */
        }

        bool
            pointsEqual(ppmd_point const a,
                ppmd_point const b) {

            return a.x == b.x && a.y == b.y;
        }
    }
}