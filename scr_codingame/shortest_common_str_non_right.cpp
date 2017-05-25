#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N;
    cin >> N; cin.ignore();
    
    std::set<std::string> sequences;
    
    for (int i = 0; i < N; i++) {
        string subseq;
        cin >> subseq; cin.ignore();
        
        sequences.insert(subseq);
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    if (N  > 1)
    {
        std::string str_union = *sequences.begin();
        sequences.erase(str_union);
        
        while (!sequences.empty())
        {
            const std::string seq = *sequences.begin();
            sequences.erase(seq);
                   
            bool bfound = false;
            // loop over first seq
            int j;
            for (j = 0; j < str_union.length() && !bfound; j++)
            {       
                // loop over second seq
                for (int k = 0; k < seq.length(); k++)
                {
                    if (j + k == str_union.length()) {
                        bfound = true;
                        break; // reach the end of first word
                    }
                    
                    if (str_union[j + k] != seq[k]){
                        break;
                    }    
                }
            }
            
            if (bfound){
                
                // check not substring
                
                str_union = str_union.substr(0, j - 1) + seq;
                
                
                //cerr << j << ' ' << str_union << endl;
                //cout << j << ' ' << str_union.substr(0, j + 1) << endl;
            }
            else{
                 
                if (str_union.find(seq) == std::string::npos){
                    str_union += seq;
                }
               // cerr << str_union << endl;
            }
        }
        cerr << str_union << endl;
        cout << str_union.length() << endl;   
        
    }
}