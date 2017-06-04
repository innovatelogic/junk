#pragma once
#include "defexport.h"
#include <cmath>
#include <assert.h>

namespace junk
{
    namespace tic_tac_toe
    {
        enum class ETicTacField
        {
            empty = 0,
            zero,
            cross
        };

        template<typename>
        int convert_field_3x3(const int board[3][3])
        {
            int out = 0;
            
            for (size_t row = 0; row < 3; row++)
            {
                for (size_t col = 0; col < 3; col++)
                {
                    int factor;

                    const int &field = (int)board[row][col];
                    
                    if (field == (int)ETicTacField::empty){
                        factor = 0;
                    }
                    else if (field == (int)ETicTacField::zero){
                        factor = 1;
                    }
                    else if (field == (int)ETicTacField::cross){
                        factor = 2;
                    }
                    else{
                        assert(false);
                    }

                    out += field * (int)std::pow(3, (row * 3) + col);
                }
            }

            return out;
        }

        template<typename>
        void convert_int_to_field(int val, int board[3][3])
        {
            for (int row = 0; row < 3; row++)
            {
                for (int col = 0; col < 3; col++)
                {
                    static ETicTacField arr[] = { ETicTacField::empty, ETicTacField::zero, ETicTacField::cross };
                    
                    board[row][col] = (int) (arr[val % 3]);

                    val /= 3;
                }
            }
        }

        template<typename>
        int checkWin_3x3(int board[3][3])
        {
            for (int row = 0; row < 3; row++)
            {
                if (board[row][0] != (int)ETicTacField::empty &&
                    board[row][0] == board[row][1] &&
                    board[row][1] == board[row][2]) {
                    return board[row][0];
                }
            }

            for (int col = 0; col < 3; col++)
            {
                if (board[0][col] != (int)ETicTacField::empty &&
                    board[0][col] == board[1][col] &&
                    board[1][col] == board[2][col]) {
                    return board[1][col];
                }
            }

            if (board[0][0] != (int)ETicTacField::empty &&
                board[0][0] == board[1][1] &&
                board[1][1] == board[2][2]) {
                return board[0][0];
            }

            if (board[0][2] != (int)ETicTacField::empty &&
                board[0][2] == board[1][1] &&
                board[1][1] == board[2][0]) {
                return board[0][2];
            }

            return board[0][2];
        }
    }
}