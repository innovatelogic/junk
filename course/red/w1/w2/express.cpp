#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

class RouteManager 
{
public:
void AddRoute(int start, int finish) 
{
    reachable_lists_[start].insert(finish);
    reachable_lists_[finish].insert(start);
}

int FindNearestFinish(int start, int finish) const
{
    int result = abs(start - finish);
    if (reachable_lists_.count(start) < 1) {
        return result;
    }

    const std::set<int>& reachable_stations = reachable_lists_.at(start);
    if (!reachable_stations.empty())
    {
        std::set<int>::const_iterator lb = reachable_stations.lower_bound(finish);

        //std::cout << finish << " " << *lb << std::endl;

        if (lb != reachable_stations.end())
        {
            // right check
            int val = abs(*lb - finish);
            if (val < result){
                result = val;
            }

            // left check
            if (lb != reachable_stations.begin())
            {
                int val = abs(*(--lb) - finish);
                //std::cout << "right" << " " << *lb << " " << val << std::endl;
                if (val < result){
                    result = val;
                }
            }    
        } 
        else 
        {
            // border check
            int val = abs(*(--lb) - finish);
              if (val < result){
                    result = val;
            }
        }
    }
    return result;
  }

private:
  map<int, std::set<int>> reachable_lists_;
};


int main()
{
  RouteManager routes;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) 
  {
    string query_type;
    cin >> query_type;
    int start, finish;
    cin >> start >> finish;
    if (query_type == "ADD") {
      routes.AddRoute(start, finish);
    } else if (query_type == "GO") {
      cout << routes.FindNearestFinish(start, finish) << "\n";
    }
  }

  return 0;
}