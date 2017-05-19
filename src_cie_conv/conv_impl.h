#pragma once

#include "defexport.h"
#include "mathlib.h"
#include <string>

namespace junk
{
	namespace cie_conv
	{
		class CIE_EXPORT CieConvertorImpl
		{
			public:
				CieConvertorImpl();
				~CieConvertorImpl();

                void Generate();

                bool Save(const std::string &filename);
			
            protected:

                static void makeAllBlack(pixel** const pixels,
                    unsigned int const cols,
                    unsigned int const rows);

                static void fillInTongue(pixel **          const pixels,
                        int                        const pixcols,
                        int                        const pixrows,
                        pixval                     const maxval,
                        const struct colorSystem * const cs);

                static void drawTongueOutline(pixel ** const pixels,
                        int    const pixcols,
                        int    const pixrows,
                        pixval const maxval,
                        bool   const upvp,
                        int    const xBias,
                        int    const yBias);

                static void DrawPlackanLocus(pixel ** const pixels, int    const pixcols,
                    int    const pixrows,
                    pixval const maxval,
                    const struct colorSystem * const cs);

			private:
                const size_t SIZE_ROWS;
                const size_t SIZE_COLS;

                struct Canvas *m_canvas;
                pixel **pixels;
        };
	}
}