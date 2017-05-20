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
            void DrawCIEPlotOutline(pixval maxval);
            void DrawPlackanLocus(pixval const maxval);
            void PlotCIESpace(pixval const maxval, const struct colorSystem * const cs);

            void line(
                pixval        const maxval,
                pos_point     const p0,
                pos_point     const p1,
                const void *  const clientdata);

        private:
            void Allocate();
            void Free();

            void FillCIE(pixval const maxval, const struct colorSystem * const cs);

        private:
            pixel **m_pixels;
            const size_t m_rows;
            const size_t m_cols;
        };
    }
}