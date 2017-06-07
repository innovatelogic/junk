#include "../cie_plot.h"
#include "../px_canvas.h"

#include <stdio.h>
#include <new>
#include <limits>
#include <gtest/gtest.h>

#if (defined(ES_WINDOWS))
#include <windows.h>
#pragma warning (disable : 4996) // fopen warn
#endif

namespace cie
{
    namespace cie_plot
    {
        extern bool FileExists(const std::wstring &path);

        //----------------------------------------------------------------------------------------------
        TEST(Cie_Plot, MaskPlotSave)
        {
            std::unique_ptr<cie::cie_plot::CiePlot> convertor(new cie::cie_plot::CiePlot()); 

            const int mask[] = { 
                0, 0, 0, // 0
                0, 0, 0,
                0, 0, 0,

                0, 0, 0, // 1
                0, 1, 0,
                0, 0, 0,

                0, 0, 0, // 2
                1, 1, 0,
                0, 0, 0,

                0, 0, 0, // 3
                1, 1, 0,
                0, 1, 0,

                0, 0, 0, // 4
                1, 1, 1,
                0, 1, 0,

                0, 0, 1, // 5
                1, 1, 1,
                0, 1, 0,

                0, 0, 1, // 6
                1, 1, 1,
                1, 1, 0,

                1, 0, 1, // 7
                1, 1, 1,
                1, 1, 0,

                1, 0, 1, // 8
                1, 1, 1,
                1, 1, 1,

                1, 1, 1, // 9
                1, 1, 1,
                1, 1, 1,
            };

            const int N = 3;
            convertor->Plot();
            convertor->Mask(mask, N, 9); // (sizeof(mask) / sizeof(int)) / (N * N)

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
            std::wstring filename = path + std::wstring(TEXT("\\1_mask.ppm"));
            
            bool bRes = convertor->Save(filename);
            
            EXPECT_TRUE(bRes && FileExists(filename));
        }

    }
}