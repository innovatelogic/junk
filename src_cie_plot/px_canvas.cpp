#include "px_canvas.h"
#include "px_draw_helper.h"
#include "cie_model_helper.h"
#include "common.h"
#include <algorithm>
#include <assert.h>

namespace cie
{
    namespace cie_plot
    {
        //----------------------------------------------------------------------------------------------
        void Canvas::Allocate()
        {
            if (m_rows > 0 && m_cols > 0)
            {
                m_pixels = new pixel*[m_rows];
                for (size_t r = 0; r < m_rows; r++) {
                    m_pixels[r] = new pixel[m_cols];
                }
            }
            else
            {
                throw std::bad_alloc();
            }
        }

        //----------------------------------------------------------------------------------------------
        void Canvas::Free()
        {
            for (size_t r = 0; r < m_rows; r++) {
                delete[] m_pixels[r];
            }
            delete[] m_pixels;
        }

        //----------------------------------------------------------------------------------------------
        void Canvas::FillColor(pixel color)
        {
            for (size_t row = 0; row < m_rows; ++row) {
                for (size_t col = 0; col < m_cols; ++col) {
                    m_pixels[row][col] = color;
                }
            }
        }

        //----------------------------------------------------------------------------------------------
        void Canvas::DrawCIEPlotOutline()
        {
            if (m_pixels)
            {
                pixel rgbcolor = { Maxval , Maxval , Maxval };
 
                int lx, ly;
                int fx, fy;

                for (int wavelength = 380; wavelength <= 700; wavelength += 5)
                {
                    int icx, icy;

                    computeMonochromeColorLocation(wavelength, m_rows, m_cols, &icx, &icy);

                    if (wavelength > 380)
                    {
                        line({ lx, ly }, { icx, icy }, rgbcolor);
                    }
                    else {
                        fx = icx;
                        fy = icy;
                    }
                    lx = icx;
                    ly = icy;
                }
                line({ lx, ly }, { fx, fy }, rgbcolor);
            }
        }

        //----------------------------------------------------------------------------------------------
        void Canvas::DrawPlackanLocus(int t0, int t1)
        {
            if (m_pixels)
            {
                if (t0 > t1) {
                    std::swap(t0, t1);
                }

                double lx = -1, ly = -1;
                double x, y;

                const double pow_10_9 = std::pow(10, 9);
                const double pow_10_6 = std::pow(10, 6);
                const double pow_10_3 = std::pow(10, 3);

                for (int t = t0; t <= t1; t += 5)
                {
                    double T_pow_3 = std::pow(t, 3);
                    double T_pow_2 = std::pow(t, 2);

                    double M1 = pow_10_9 / T_pow_3;
                    double M2 = pow_10_6 / T_pow_2;
                    double M3 = pow_10_3 / t;

                    if (t < 1500 || t > 25000) {
                        continue;
                    }

                    if (t <= 4000) {
                        x = pl_x_temperature[0][0] * M1 + pl_x_temperature[0][1] * M2 + pl_x_temperature[0][2] * M3 + pl_x_temperature[0][3];
                    }
                    else {
                        x = pl_x_temperature[1][0] * M1 + pl_x_temperature[1][1] * M2 + pl_x_temperature[1][2] * M3 + pl_x_temperature[1][3];
                    }

                    if (t <= 2222) {
                        y = pl_y_temperature[0][0] * std::pow(x, 3) + pl_y_temperature[0][1] * std::pow(x, 2) + pl_y_temperature[0][2] * x + pl_y_temperature[0][3];
                    }
                    else if (t > 2222 && t <= 4000) {
                        y = pl_y_temperature[1][0] * std::pow(x, 3) + pl_y_temperature[1][1] * std::pow(x, 2) + pl_y_temperature[1][2] * x + pl_y_temperature[1][3];
                    }
                    else {
                        y = pl_y_temperature[2][0] * std::pow(x, 3) + pl_y_temperature[2][1] * std::pow(x, 2) + pl_y_temperature[2][2] * x + pl_y_temperature[2][3];
                    }

                    double cx = ((double)x) * (m_cols - 1);
                    double cy = m_rows - ((double)y) * (m_rows - 1);

                    if (t > t0)
                    {
                        static const pixel rgbcolor = { 0, 0, 0 };
                        if ((cx >= 0 && cx < m_rows) && (cy >= 0 && cy < m_cols) &&
                            (lx >= 0 && lx < m_rows) && (ly >= 0 && ly < m_cols))
                        {
                            line({ (int)lx, (int)ly }, { (int)cx, (int)cy }, rgbcolor);
                        }
                    }

                    lx = cx;
                    ly = cy;
                }
            }
        }

        //----------------------------------------------------------------------------------------------
        void Canvas::line(
                const pos_point &p0,
                const pos_point &p1,
                const pixel &color)
        {
            if (m_pixels)
            {
                if (p0 == p1)
                {
                    /* just a point */
                    drawPoint(m_pixels, p0, color);
                }
                else {
                    /* Draw, using a simple DDA. */
                    if (abs(p1.x - p0.x) > abs(p1.y - p0.y)) {
                        drawShallowLine(m_pixels, p0, p1, color);
                    }
                    else
                    {
                        drawSteepLine(m_pixels, p0, p1, color);
                    }
                }
            }
        }

        //----------------------------------------------------------------------------------------------
        void Canvas::PlotCIESpace()
        {
            DrawCIEPlotOutline();
            FillCIE();
        }

        //----------------------------------------------------------------------------------------------
        void Canvas::FillCIE()
        {
            if (m_pixels)
            {
                for (int y = 0; y < (int)m_cols; ++y)
                {
                    int leftEdge; /* x position of leftmost pixel */
                    int rightEdge; /* rightmost */

                    if (findCIERowRange(m_pixels, m_cols, y, &leftEdge, &rightEdge))
                    {
                        for (int x = leftEdge; x <= rightEdge; ++x)
                        {
                            double cx, cy, cz, jr, jg, jb, jmax;

                            cx = ((double)x) / (m_cols - 1);
                            cy = 1.0 - ((double)y) / (m_rows - 1);
                            cz = 1.0 - (cx + cy);

                            xyz_to_rgb(&CIEsystem, cx, cy, cz, &jr, &jg, &jb);

                            constrain_rgb(&jr, &jg, &jb);

                            /* Scale to max(rgb) = 1. */
                            jmax = std::max(jr, std::max(jg, jb));
                            if (jmax > 0) {
                                jr = jr / jmax;
                                jg = jg / jmax;
                                jb = jb / jmax;
                            }

                            int mx = Maxval;

                            m_pixels[y][x].r = static_cast<int>(mx * jr);
                            m_pixels[y][x].g = static_cast<int>(mx * jg);
                            m_pixels[y][x].b = static_cast<int>(mx * jb);
                        }
                    }
                }
            }
        }

        //----------------------------------------------------------------------------------------------
        void Canvas::GaussianBlur()
        {

        }

        //----------------------------------------------------------------------------------------------
        void Canvas::Mask(const int *mask, size_t size, size_t sample_count)
        {
            assert(mask);

            const size_t sr = m_rows / size;
            const size_t sc = m_cols / size;

            for (size_t i = 0; i < sr; i++)
            {
                for (size_t j = 0; j < sr; j++)
                {
                    const size_t row = i * size;
                    const size_t col = j * size;

                    const float intencity = GetAverageIntencity(row, col, size); // 0..1
					const size_t sample_idx = static_cast<size_t>(sample_count * intencity);

                    SetSample(row, col, mask + (sample_idx * (size * size)), size);
                }
            }
        }

        //----------------------------------------------------------------------------------------------
        float Canvas::GetAverageIntencity(size_t row, size_t col, size_t size)
        {
            float out = 0.f;

            const size_t MAX_PX_VALUE = 255 * 3;
            size_t px_count = 0;

            if (row < m_rows && col < m_cols)
            {
                const size_t max_row = row + size;
                const size_t max_col = col + size;

                bool out_of_bounds = false;
                for (size_t i = row; i < max_row && !out_of_bounds; i++)
                {
                    for (size_t j = col; j < max_col; j++)
                    {
                        if (j >= m_cols) { continue; }
                        if (i >= m_rows) { out_of_bounds = true; break; }

                        out += (float)(m_pixels[i][j].r + m_pixels[i][j].g + m_pixels[i][j].b) / MAX_PX_VALUE;
                        px_count++;
                    }
                }
            }
            return px_count > 0 ? out / px_count : 0.f;
        }

        //----------------------------------------------------------------------------------------------
        void Canvas::SetSample(size_t row, size_t col, const int *mask, size_t size)
        {
            if (mask && row < m_rows && col < m_cols)
            {
                const size_t max_row = row + size;
                const size_t max_col = col + size;

                size_t px_count = 0;

                bool out_of_bounds = false;
                for (size_t i = row; i < max_row && !out_of_bounds; i++)
                {
                    for (size_t j = col; j < max_col; j++)
                    {
						int px_idx = px_count++;

                        if (j >= m_cols) { continue; }
                        if (i >= m_rows) { out_of_bounds = true; break; }

                        const int mask_value = mask[px_idx];

                        m_pixels[i][j].r = mask_value == 0 ? 0 : 255;
                        m_pixels[i][j].g = mask_value == 0 ? 0 : 255;
                        m_pixels[i][j].b = mask_value == 0 ? 0 : 255;
                    }
                }
            }
        }   
    }
}