#pragma once

#include <vector>
#include <math.h>

namespace junk
{
    namespace matrix_cw
    {
        //---------------------------------------------------------------------------------
        // Write a function with the following signature that, given a matrix of integers,
        // builds a string with the entries of that matrix appended in clockwise order.
        //---------------------------------------------------------------------------------

        template<typename T>
        void GetRingValuesCW(T *Matrix, int IndexRing, int NumRows, int NumColumns, std::vector<T> &OutBuffer)
        {
            const int StartIndex = IndexRing * NumColumns + IndexRing;
            int ArrayMaxIndex = NumRows * NumColumns;
            int CurrentIndex, Limit;

            CurrentIndex = StartIndex;

            // iterate L2R
            Limit = StartIndex + (NumColumns - IndexRing * 2);
            for (int Index = CurrentIndex; Index < Limit; ++Index)
            {
                OutBuffer.push_back(Matrix[Index]);
                CurrentIndex = Index;
            }

            // iterate Top2Bottom
            bool bHorizontalShift = false;

            Limit = ArrayMaxIndex - (IndexRing * NumColumns);
            for (int Index = CurrentIndex + NumColumns; Index < Limit; Index += NumColumns, bHorizontalShift = true)
            {
                OutBuffer.push_back(Matrix[Index]);
                CurrentIndex = Index;
            }

            // iterate R2L
            bool bLeftToRightShift = false;

            Limit = CurrentIndex - (NumColumns - IndexRing * 2);
            for (int Index = CurrentIndex - 1; bHorizontalShift && Index > Limit; --Index, bLeftToRightShift = true)
            {
                OutBuffer.push_back(Matrix[Index]);
                CurrentIndex = Index;
            }

            // iterate B2T
            for (int Index = CurrentIndex - NumColumns; bLeftToRightShift && Index > StartIndex; Index -= NumColumns)
            {
                OutBuffer.push_back(Matrix[Index]);
            }
        }

        template<typename T>
        void MatrixCW(T *Matrix, int NumRows, int NumColumns, std::vector<T> &OutBuffer)
        {
            if (Matrix != nullptr && NumRows > 0 && NumColumns > 0)
            {
                int ChrIdx = 0;

                int NumCircles = (int)ceil(((NumRows < NumColumns) ? NumRows : NumColumns) / 2.f);

                for (int Index = 0; Index < NumCircles; ++Index)
                {
                    GetRingValuesCW<T>(Matrix, Index, NumRows, NumColumns, OutBuffer);
                }
            }
        }
    }

}