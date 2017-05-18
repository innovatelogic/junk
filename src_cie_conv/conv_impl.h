#pragma once

#include "defexport.h"
#include "bmpread.h"
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


                static void
                    fillInTongue(pixel **          const pixels,
                        int                        const pixcols,
                        int                        const pixrows,
                        pixval                     const maxval,
                        const struct colorSystem * const cs,
                        bool                       const upvp,
                        int                        const xBias,
                        int                        const yBias,
                        bool                       const highlightGamut);

                static void
                    drawTongueOutline(pixel ** const pixels,
                        int    const pixcols,
                        int    const pixrows,
                        pixval const maxval,
                        bool   const upvp,
                        int    const xBias,
                        int    const yBias);

			private:
                const size_t SIZE_ROWS;
                const size_t SIZE_COLS;

                pixel **pixels;
        };
	}
}