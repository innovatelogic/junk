#pragma once

#include "defexport.h"
#include "common.h"
#include "px_canvas.h"
#include <string>
#include <memory>

namespace junk
{
	namespace cie_conv
	{
        //class Canvas;

		class CiePlotImpl
		{
			public:
                CiePlotImpl();
				~CiePlotImpl();

                void Plot();

                bool Save(const std::wstring &filename);
			
            protected:
			private:
                const size_t SIZE_ROWS;
                const size_t SIZE_COLS;

                std::unique_ptr<Canvas> m_canvas;
        };
	}
}