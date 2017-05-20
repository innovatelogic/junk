#include "px_canvas.h"

namespace junk
{
    namespace cie_conv
    {
        void Canvas::allocate()
        {
            pixels = new pixel*[rows];
            for (size_t r = 0; r < rows; r++) {
                pixels[r] = new pixel[cols];
            }
        }

        void Canvas::free()
        {
            for (size_t r = 0; r < rows; r++) {
                delete[] pixels[r];
            }
            delete[] pixels;
        }
    }
}