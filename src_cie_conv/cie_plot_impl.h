#pragma once

#include "defexport.h"
#include "common.h"
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

                void Plot();

                bool Save(const std::string &filename);
			
            protected:
			private:
                const size_t SIZE_ROWS;
                const size_t SIZE_COLS;

                class Canvas *m_canvas;
        };
	}
}