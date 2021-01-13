#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <map>

using namespace std;

struct DomainNode
{
    bool banned;

    std::map<std::string_view, std::shared_ptr<DomainNode>> subdomains;

    DomainNode(bool banned = false)
    : banned(banned)
    {
    }

    void Add(const string_view &domain)
    {
        //std::cout << "Add domain: " << domain << std::endl;

        auto rpos = domain.find_last_of('.');

        if (rpos == std::string::npos)
        {
            if (subdomains.count(domain) == 0)
            {
                //std::cout << "Add domain banned: " << domain << std::endl;
                subdomains[domain] = std::make_shared<DomainNode>(true);
            }
            else
            {
                subdomains[domain]->banned = true;
            }
        }
        else
        {

            //std::cout << "rpos: " << rpos << std::endl;

            auto left_name = domain.substr(0, rpos);
            auto domain_name = domain.substr(rpos + 1);

            //std::cout << "Split domain: " << left_name << " | " << domain_name << std::endl;

            if (subdomains.count(domain_name) == 0)
            {
                auto new_domain = std::make_shared<DomainNode>(false);
                
                new_domain->Add(left_name);

                subdomains[domain_name] = new_domain;
            }
            else
            {
                subdomains[domain_name]->Add(left_name);
            }
        }
    }

    void Print(int tab)
    {
        for (const auto &it : subdomains)
        {
            for (int i = 0; i < tab; i++) { std::cout << "\t"; }
            std::cout << it.first << " " << it.second->banned << std::endl;

            it.second->Print(tab + 1);
        }
    }

    bool IsBanned(const std::string_view &domain) const
    {
        //std::cout << "check: " << domain << std::endl;

        auto rpos = domain.find_last_of('.');

        if (rpos == std::string::npos)
        {
            if (subdomains.count(domain) > 0) {
                return subdomains.at(domain)->banned;
            }
        }
        else
        {
            auto left_name = domain.substr(0, rpos);
            auto domain_name = domain.substr(rpos + 1);

            if (subdomains.count(domain_name) > 0)
            {
                if (subdomains.at(domain_name)->banned) {
                    return true;
                }

                return subdomains.at(domain_name)->IsBanned(left_name);
            }
        }
        return false;
    }
};

struct TDomainTree
{
    DomainNode root;

    TDomainTree(const std::vector<std::string> &domains)
    {
        for (const string_view &domain : domains)
        {
            if (domain.empty()){
                continue;
            }
            root.Add(domain);
        }
    }

    bool IsBanned(const std::string_view &domain) const
    {
        return root.IsBanned(domain);
    }

    void Print()
    {
        root.Print(0);
    }
};


bool IsSubdomain(string_view subdomain, string_view domain) {
  auto i = subdomain.size() - 1;
  auto j = domain.size() - 1;
  while (i >= 0 && j >= 0) {
    if (subdomain[i--] != domain[j--]) {
      return false;
    }
  }
  return (i < 0 && domain[j] == '.')
      || (j < 0 && subdomain[i] == '.');
}


vector<string> ReadDomains() {
  size_t count;
  cin >> count;

  vector<string> domains;
  for (size_t i = 0; i < count; ++i)
{
    string domain;
    //getline(cin, domain);
    std::cin >> domain;
    domains.push_back(domain);
  }
  return domains;
}


int main() 
{
  vector<string> banned_domains = ReadDomains();

  TDomainTree domains(banned_domains);

  //domains.Print();

  const vector<string> domains_to_check = ReadDomains();


    for (const string_view domain : domains_to_check)
    {
        if (domains.IsBanned(domain))
        {
            cout << "Bad" << endl;
        }
        else
        {
            cout << "Good" << endl;
        }
    }
  //domains.Print();

  //


  /*for (string_view domain : banned_domains)
  {
    reverse(begin(domain), end(domain));
  }

  sort(begin(banned_domains), end(banned_domains));

  for (string& domain : banned_domains) 
  {

  }*/
   

/*

  size_t insert_pos = 0;
  for (string& domain : banned_domains) {
    if (insert_pos == 0 || !IsSubdomain(domain, banned_domains[insert_pos - 1])) {
      swap(banned_domains[insert_pos++], domain);
    }
  }
  banned_domains.resize(insert_pos);

  for (const string_view domain : domains_to_check) {
    if (const auto it = upper_bound(begin(banned_domains), end(banned_domains), domain);
        it != begin(banned_domains) && IsSubdomain(domain, *prev(it))) {
      cout << "Good" << endl;
    } else {
      cout << "Bad" << endl;
    }
  }*/
  return 0;
}