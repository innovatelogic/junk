
#include "../cie_plot.h"
#include <stdio.h>
#include <gtest/gtest.h>

#if (defined(ES_WINDOWS))
#include <windows.h>
#pragma warning (disable : 4996) // fopen warn
#endif
namespace junk
{
    namespace cie_conv
    {
        bool FileExists(const std::wstring &path)
        {
            if (path.empty()) {
                return false;
            }

            FILE *file = _wfopen(path.c_str(), L"rb");

            if (file == nullptr) {
                return false;
            }
            fclose(file);
            return true;
        }

        TEST(Cie_Plot, PlotSave)
        {
            junk::cie_conv::CiePlot *convertor = new junk::cie_conv::CiePlot();

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
            //path = ".";
#endif//ES_WINDOWS
            std::wstring filename = path + std::wstring(TEXT("\\1.ppm"));
            
            bool bRes = convertor->Save(filename);
            
            EXPECT_TRUE(bRes && FileExists(filename));
        }
    }
}