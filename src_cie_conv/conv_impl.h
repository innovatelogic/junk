#pragma once

#include "defexport.h"
#include "mathlib.h"
#include <string>

namespace junk
{
	namespace cie_conv
	{
		class CIE_EXPORT CiePlotImpl
		{
			public:
                CiePlotImpl();
				~CiePlotImpl();

                void Generate();

                bool Save(const std::string &filename);
			
            protected:
			private:
                const size_t SIZE_ROWS;
                const size_t SIZE_COLS;

                class Canvas *m_canvas;
        };
	}
}