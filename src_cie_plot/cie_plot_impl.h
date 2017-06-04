#pragma once

#include "defexport.h"
#include "common.h"
#include "include/iplot_impl.h"
#include <string>
#include <memory>

namespace cie
{
	namespace cie_plot
	{
		class CiePlotImpl : public IPlotImpl
		{
			public:
                CiePlotImpl();
				virtual ~CiePlotImpl();

                bool Plot() override;
                bool Save(const std::wstring &filename) override;

                void GaussianBlur() override;
			
            protected:
			private:
                static const size_t SIZE_ROWS = 1024;
                static const size_t SIZE_COLS = 1024;

                std::unique_ptr<class Canvas> m_canvas;
        };
	}
}