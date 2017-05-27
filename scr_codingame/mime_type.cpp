#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <locale>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N; // Number of elements which make up the association table.
    cin >> N; cin.ignore();
    int Q; // Number Q of file names to be analyzed.
    cin >> Q; cin.ignore();
    
    typedef unordered_map<std::string, std::string> MMap;
    MMap mime_map;
    
    for (int i = 0; i < N; i++) {
        string EXT; // file extension
        string MT; // MIME type.
        cin >> EXT >> MT; cin.ignore();
    
        std::transform (EXT.begin(), EXT.end(), EXT.begin(), ::tolower);
        mime_map[EXT] = MT;
    }
    
    
    
    for (int i = 0; i < Q; i++) {
        string FNAME; // One file name per line.
        getline(cin, FNAME);
        
        std::string type = "UNKNOWN";
        
        size_t pos = FNAME.rfind('.');
        if (pos != std::string::npos)
        {
            std::string ext = FNAME.substr(pos + 1);
            
            std::transform (ext.begin(), ext.end(), ext.begin(), ::tolower);
            MMap::iterator ifind = mime_map.find(ext);
            
            if (ifind != mime_map.end())
            {
                type = ifind->second;   
            }
        }
        cout << type << endl;
    }
}