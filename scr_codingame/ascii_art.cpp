#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Token
{
    std::vector<std::string> rows;
};

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int L;
    cin >> L; cin.ignore();
    int H;
    cin >> H; cin.ignore();
    string T;
    getline(cin, T);
    
    
    std::string ASCII;
    for (int i = 0; i < H; i++) {
        string ROW;
        getline(cin, ROW);
       
        ASCII+= ROW;
        
      //  cerr << ROW.size() << endl;
    }
   
    std::map<char, Token> letters;
    
    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ?";
    
    //cerr << alphabet.size() << endl;
    
    for (int i = 0; i < alphabet.size(); i++)
    {
         char chr = alphabet[i];
         letters[chr] = Token();
         
         int letter_pos = L * i; 
         
         cerr << chr << endl;
         
         for (int h = 0; h < H; h++)
         {             
            //cerr << ASCII.substr(letter_pos, L) << endl;
            letters[chr].rows.push_back(ASCII.substr(letter_pos, L)); 
            letter_pos += ASCII.size() / H;
         }
    }
    
    
    for (int h = 0; h < H; h++)
    {
        std::string output;
        for (int i = 0; i < T.size(); i++)
        {
            char chr = std::toupper(T[i]);
            
            if (letters.find(chr) == letters.end()){
                chr = '?';
            }
            
            output += letters[chr].rows[h];
        }
        
       // cerr << output.c_str() << endl;
        cout << output.c_str() << endl;
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    
    
}