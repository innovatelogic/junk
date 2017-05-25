#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 * ---
 * Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders.
 **/
int main()
{
    int lightX; // the X position of the light of power
    int lightY; // the Y position of the light of power
    int initialTX; // Thor's starting X position
    int initialTY; // Thor's starting Y position
    cin >> lightX >> lightY >> initialTX >> initialTY; cin.ignore();

    // game loop
    while (1) 
    {
        int remainingTurns; // The remaining amount of turns Thor can move. Do not remove this line.
        cin >> remainingTurns; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        int dx = lightX - initialTX;
        int dy = lightY - initialTY;
        
        cerr << lightX << ';' << lightY << " --- " << initialTX << ';' << initialTY << endl; 
        
        cerr << dx << ' ' << dy; 
    
        std::string move;
        
        if (dy == 0)
        {
            move = (dx > 0) ? "E" : "W";
        }
        else if (dx == 0)
        {
            move = (dy > 0) ? "S" : "N";
        }
        else// if (fabs(dx) > fabs(dy)) // move more horizontal than vertical
        {
            if (dx > 0) // east move
            {
                if (dy > 0) // south
                {
                     if ((fabs(dx) > fabs(dy)))
                     {
                        move = "E";
                        initialTX++;
                     }
                     else if (fabs(dx) < fabs(dy))
                     {
                         move = "S";
                         initialTY++;
                     }
                     else
                     {
                        move = "SE";
                     
                        initialTX++;
                        initialTY++;
                     }
                    
                }
                else // north
                {
                     if (fabs(dx) > fabs(dy)) // move more horizontal than vertical
                     {
                         move = "E";
                         initialTX++;
                     }
                     else if(fabs(dx) < fabs(dy))
                     {
                         move = "N";
                         initialTX--;
                     }
                     else
                     {
                        move = "NE";
                                         
                        initialTX--;
                        initialTY++;
                     }
                }
                 
            }
            else // west
            {
                if (dy > 0)
                {
                     if (fabs(dx) > fabs(dy)) // move more horizontal than vertical
                     {
                          move = "W";
                    
                        initialTX--;
                     }
                     else if (fabs(dx) < fabs(dy))
                     {
                         move = "S";
                         initialTY++;
                     }
                     else
                     {
                        move = "SW";
                    
                        initialTX--;
                        initialTY++;
                     }
                }
                else
                {
                   
                     if (fabs(dx) > fabs(dy)) // move more horizontal than vertical
                     {
                          move = "W";
                          initialTX--;
                     }
                     else if (fabs(dx) < fabs(dy))
                     {
                         move = "N";
                         initialTY--;
                     }
                        
                    else
                    {
                     move = "NW";
                     initialTX--;
                     initialTY--;
                    }
                }
                 
            }        
        }

        // A single line providing the move to be made: N NE E SE S SW W or NW
        cout << move.c_str() << endl;
    }
}