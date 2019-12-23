#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using t_busstops = std::map<std::string, std::vector<std::string>>;
using t_order_busstops = std::vector<std::string>;


void new_bus(t_busstops &busstops, t_order_busstops &busstops_ordered)
{
    std::string n;
    int stop_count;
    std::cin >> n >> stop_count;

    busstops[n].resize(stop_count);

    int i = 0;
    while (stop_count)
    {
        std::cin >> busstops[n][i];

        ++i;
        --stop_count;
    }

    busstops_ordered.push_back(n);
}

void buses_for_stop(t_busstops &busstops, t_order_busstops &busstops_order, const std::string &stop)
{
    std::vector<std::string> res;

    for (const auto &iter : busstops_order)
    {
        if (std::find(begin(busstops[iter]), end(busstops[iter]), stop) != busstops[iter].end())
        {
            res.push_back(iter);
        }
    }

    if (res.empty())
    {
        std::cout << "No stop" << std::endl;
    }
    else
    {
        for (const auto &i : res)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
}

void stops_for_bus(t_busstops &busstops, t_order_busstops &busstops_order, const std::string &bus)
{
    if (busstops.count(bus) == 0)
    {
        std::cout << "No bus" << std::endl;
    }
    else
    {
        std::vector<std::pair<std::string, std::vector<std::string>>> stop_table;

        for (const auto &stop : busstops[bus])
        {
            stop_table.push_back(std::make_pair(stop, std::vector<std::string>()));

            for (const auto &bus2 : busstops_order)
            {
                if (bus2 != bus)
                {
                    if (std::find(begin(busstops[bus2]), end(busstops[bus2]), stop) != busstops[bus2].end())
                    {
                        stop_table[stop_table.size() - 1].second.push_back(bus2);
                    }
                }
            }
        }

        for (const auto &it : stop_table)
        {
            std::cout << "Stop " << it.first << ": ";

            if (it.second.empty())
            {
                std::cout << "no interchange";
            }
            else
            {
                for (const auto &it_bus : it.second)
                {
                    std::cout << it_bus << " ";
                }
            }
            std::cout << std::endl;
        }
    }
}

void all_busses(t_busstops &busstops)
{

    if (busstops.empty())
    {
        std::cout << "No buses" << std::endl;
    }
    else
    {
        for (auto iter : busstops)
        {
            std::cout << "Bus " << iter.first << ": ";

            for (const auto &it_bus : iter.second)
            {
                std::cout << it_bus << " ";
            }

            std::cout << std::endl;
        }
    }
}

int main()
{
    t_busstops busstops;
    t_order_busstops t_ordered;

    int q;
    std::cin >> q;

    std::string op;

    while (q > 0)
    {
        std::cin >> op;

        if (op == "NEW_BUS")
        {
            new_bus(busstops, t_ordered);
        }
        else if (op == "BUSES_FOR_STOP")
        {
            std::string stop;
            std::cin >> stop;
            buses_for_stop(busstops, t_ordered, stop);
        }
        else if (op == "STOPS_FOR_BUS")
        {
            std::string bus;
            std::cin >> bus;

            stops_for_bus(busstops, t_ordered, bus);
        }
        else if (op == "ALL_BUSES")
        {
            all_busses(busstops);
        }
        --q;
    }
    return 0;
}