#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <math.h>
#include <limits>

using namespace std;

struct Defib
{
    int id;
    std::string name;
    std::string adress;
    std::string phone;
    double lon;
    double lat;
    
    Defib(int id, const std::string &name, const std::string &adress, const std::string &phone, double lon, double lat)
    : id(id)
    , name(name)
    , adress(adress)
    , phone(phone)
    , lon(lon)
    , lat(lat){}
};

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    string LON;
    cin >> LON; cin.ignore();
    string LAT;
    cin >> LAT; cin.ignore();
    int N;
    cin >> N; cin.ignore();
    
    
    std::vector<Defib> defibrilators;
    
    std::replace(LON.begin(),  LON.end(), ',', '.');
    std::replace(LAT.begin(),  LAT.end(), ',', '.');
        
    float user_lon = atof(LON.c_str());
    float user_lat = atof(LAT.c_str());
    
    for (int i = 0; i < N; i++) 
    {
        string DEFIB;
        getline(cin, DEFIB);
       // cerr << DEFIB.c_str() << endl;
        
        
        std::vector<std::string> tokens;
        size_t pos = 0, pos_prev = 0;
        
        while ((pos = DEFIB.find(';', pos)) != std::string::npos)
        {
            std::string token = DEFIB.substr(pos_prev, pos - pos_prev);
            tokens.push_back(token);   
            pos_prev = ++pos;
        }
        
        std::string last_token = DEFIB.substr(pos_prev);
        tokens.push_back(last_token);   
        
        //cerr << tokens[4].c_str() << " " << tokens[5].c_str() << endl;
        
        std::replace(tokens[4].begin(),  tokens[4].end(), ',', '.');
        std::replace(tokens[5].begin(),  tokens[5].end(), ',', '.');
        
        defibrilators.emplace_back( Defib(
            atoi(tokens[0].c_str()),
            tokens[1],
            tokens[2],
            tokens[3],
            atof(tokens[4].c_str()),
            atof(tokens[5].c_str())
            ));
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    std::string out = "God bless You";
    
    float min_dist = std::numeric_limits<float>::max();
    
    for (int i = 0; i < defibrilators.size(); i++)
    {
        Defib &defib = defibrilators[i];
        
        float x = (defib.lon - user_lon) * cos((user_lat + defib.lat) / 2);
        float y = (defib.lat - user_lat);
        float dist = sqrt(x * x + y * y) * 6371;
        
        if (dist < min_dist)
        {
            out = defib.name;
            cerr << dist << " " << out << endl;
            min_dist = dist;   
        }
    }
    
    cout << out.c_str() << endl;
}