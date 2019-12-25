#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>

int main()
{
    std::map<std::set<std::string>, size_t> cont;

    int n;
    std::cin >> n;

    int bus_num = 1;

    while (n > 0)
    {

        int stops_num;
        std::cin >> stops_num;

        std::set<std::string> stops;

        int idx = 0;
        while (stops_num)
        {
            std::string stop;
            std::cin >> stop;
            stops.insert(stop);
            --stops_num;
        }

        auto iter_find = cont.find(stops);
        if (iter_find == cont.end()){
            cont[stops] = bus_num;

            std::cout << "New bus " << bus_num << std::endl;
            ++bus_num;
        }
        else
        {
            std::cout << "Already exists for " << iter_find->second << std::endl;
        }

        --n;
    }

    return 0;
}