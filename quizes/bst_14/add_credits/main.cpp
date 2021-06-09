#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <assert.h>


//    A = 0
//    B = 5
//    C = 10
// 
// add 5: (5)
//    A = 0 + 5 = (5)
//    B = 5 + 5 = (10)
//    C = 10 + 5 = (15)
//    D = 8 + (-5) = (3)
//
// add 1: (6)
//    A -> (0 + 6) = 6
//    B -> (5 + 6) = 11
//    C -> (10 + 6) = 16
//    D -> (3 + 6) = 9

class Accounts
{
public:
    Accounts()
    : offset(0)
    {}

    void add_client(const std::string &id, int credit)
    {
        client_to_credit[id] = credit - offset;
        credit_to_client[credit - offset].insert(id);
    }

    void remove(const std::string &id)
    {
        auto iter_find_client = client_to_credit.find(id);
        if (iter_find_client != client_to_credit.end())
        {
            auto iter_find_credit = credit_to_client.find(iter_find_client->second);

            assert(iter_find_credit != credit_to_client.end());

            iter_find_credit->second.erase(iter_find_credit->second.find(iter_find_client->first));
            
            if (iter_find_credit->second.empty()) {
                credit_to_client.erase(iter_find_client->second);
            }

            client_to_credit.erase(iter_find_client);
        }
    }

    int lookup(const std::string &id) const
    {
        int out = 0;

        auto iter_find_client = client_to_credit.find(id);

        if (iter_find_client != client_to_credit.end()){
            out = iter_find_client->second + offset;
        }

        return out;
    }

    void add_to_all(int num)
    {
        offset += num;
    }

    std::string max()
    {
        std::string out;

        if (!credit_to_client.empty())
        {
            out = *(credit_to_client.rbegin()->second.begin());
        }

        return out;
    }

    void print()
    {
        std::cout << "client_to_credit :" << "\n";
        for (const auto p : client_to_credit) {
            std::cout << p.first << " - " << p.second + offset << std::endl;
        }

        std::cout << "credit_to_client :" << "\n";
        for (const auto p : credit_to_client) {
        
            std::cout << p.first + offset << " - ";

            for (const auto c : p.second) {
                std::cout << c << " ";
            }

            std::cout << std::endl;
        }
    }

protected:
private:
    int offset;
    std::unordered_map<std::string, int> client_to_credit;
    std::map<int, std::unordered_set<std::string> > credit_to_client;
};

int main()
{
    size_t num_commands = 0;

    std::cout << " num commands : " << std::endl;
    std::cin >> num_commands;

    Accounts accounts;

    while (num_commands > 0)
    {
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "insert")
        {
            std::string id;
            int credit;

            std::cin >> id >> credit;

            accounts.add_client(id, credit);
        }
        else if (cmd == "remove")
        {
            std::string id;
            std::cin >> id;

            accounts.remove(id);
        }
        else if (cmd == "lookup")
        {
            std::string id;
            std::cin >> id;

            std::cout << accounts.lookup(id) << std::endl;
        }
        else if (cmd == "add")
        {
            int num;
            std::cin >> num;

            accounts.add_to_all(num);
        }
        else if (cmd == "max")
        {
            std::cout << accounts.max() << std::endl;
        }
        else if (cmd == "print")
        {
            accounts.print();
        }

        --num_commands;
    }

    return 0;
}