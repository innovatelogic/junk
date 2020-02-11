#include "responses.h"

ostream& operator << (ostream& os, const BusesForStopResponse& r)
{
    if (r.t_ordered.empty())
    {
        std::cout << "No stop" << std::endl;
    }
    else
    {
        for (const auto &i : r.t_ordered)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    return os;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r) 
{
    if (r.stop_table.empty())
    {
        os << "No bus" << std::endl;
    }
    else
    {
        for (const auto &it : r.stop_table)
        {
            os << "Stop " << it.first << ": ";

            if (it.second.empty())
            {
                os << "no interchange";
            }
            else
            {
                for (const auto &it_bus : it.second)
                {
                    os << it_bus << " ";
                }
            }
            os << std::endl;
        }
    }

    return os;
}

ostream& operator << (ostream& os, const AllBusesResponse& r) 
{
    if (r.busstops.empty())
    {
        os << "No buses" << std::endl;
    }
    else
    {
        for (auto iter : r.busstops)
        {
            os << "Bus " << iter.first << ": ";

            for (const auto &it_bus : iter.second)
            {
                os << it_bus << " ";
            }

            os << std::endl;
        }
    }
    return os;
}