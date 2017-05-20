#pragma once

#include "defexport.h"
#include "common.h"

namespace junk
{
    namespace cie_conv
    {
        class Canvas
        {
            Canvas(const Canvas&) = delete;
            Canvas& operator =(const Canvas&) = delete;

        public:
            Canvas(size_t rows, size_t cols)
                : m_rows(rows)
                , m_cols(cols)
                , m_pixels(nullptr) {
                Allocate();
            }

            ~Canvas() { Free(); }

            void FillColor(pixel color);

            pixel** data() const { return m_pixels; }

            size_t rows() const { return m_rows; }
            size_t cols() const { return m_cols; }

            // CIE plot helper functions
            void DrawCIEPlotOutline();
            void DrawPlackanLocus();
            void PlotCIESpace(const struct colorSystem * const cs);

            // draw line. warn do not check bounds
            void line(
                const pos_point &p0,
                const pos_point &p1,
                const pixel &color);

        private:
            void Allocate();
            void Free();

            void FillCIE(const struct colorSystem * const cs);

        private:
            pixel **m_pixels;
            const size_t m_rows;
            const size_t m_cols;
        };
    }
}