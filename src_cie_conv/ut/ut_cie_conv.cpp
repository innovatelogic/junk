
#include "../cie_plot.h"
#include <gtest/gtest.h>

#if (defined(ES_WINDOWS))
#include <windows.h>
#endif
namespace junk
{
    namespace cie_conv
    {
        TEST(Cie_Conv, LoadBMP)
        {
            junk::cie_conv::CiePlot *convertor = new junk::cie_conv::CiePlot();

            bool bLoaded = false;
            
            convertor->Plot();

            std::wstring path;

#if (defined(ES_WINDOWS))
            wchar_t ownPth[MAX_PATH];
            HMODULE hModule = GetModuleHandle(NULL);
            if (hModule)
            {
                GetModuleFileName(hModule, ownPth, (sizeof(ownPth)));
                path = ownPth;
                path = path.substr(0, path.rfind('\\'));
            }
#else
#endif//ES_WINDOWS
            std::wstring filename = path + std::wstring(TEXT("\\1.ppm"));
            if (convertor->Save(filename))
            {
               /* convertor->Free();*/
                bLoaded = true;
            }
            EXPECT_TRUE(bLoaded);
        }
    }
}