#include <iostream>
#include <string>
#include <map>

using t_map_country = std::map<std::string, std::string>;


void change_capital(t_map_country &cont, const std::string &country, const std::string &name)
{
    if (cont.count(country) == 0)
    {
        std::cout << "Introduce new country " << country << " with capital " << name << std::endl;
    }
    else
    {
        if (cont[country] == name)
        {
            std::cout << "Country " << country << " hasn't changed its capital" << std::endl;
        }
        else
        {
            std::cout << "Country " << country << " has changed its capital from " << cont[country] << " to " << name << std::endl;
        }
    }
    
    cont[country] = name;
}

void rename_country(t_map_country &cont, const std::string &old_name, const std::string &new_name)
{
    if (cont.count(old_name) == 0 || cont.count(new_name) > 0 || old_name == new_name)
    {
        std::cout << "Incorrect rename, skip" << std::endl;
        return;
    }

    {
        std::string tmp = cont[old_name];
        cont.erase(old_name);
        cont[new_name] = tmp;

        std::cout << "Country " << old_name << " with capital " << tmp << " has been renamed to " << new_name << std::endl;
    }
}

void about(t_map_country &cont, const std::string &country)
{
    if (cont.count(country) == 0)
    {
        std::cout << "Country " << country << " doesn't exist" << std::endl;
    }
    else
    {
        std::cout << "Country " << country << " has capital " << cont[country] << std::endl;
    }
}

void dump(const t_map_country &cont)
{
    if (cont.empty())
    {
        std::cout << "There are no countries in the world" << std::endl;
    }
    else
    {
        for (auto it : cont)
        {
            std::cout << it.first << "/" << it.second << std::endl;
        }
    }
}

int main()
{
    t_map_country m_countries;

    int n;
    std::cin >> n;

    std::string op;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> op;

        if (op == "CHANGE_CAPITAL")
        {
            std::string a, b;
            std::cin >> a >> b;

            change_capital(m_countries, a, b);
        }
        else if (op == "RENAME")
        {
            std::string a, b;
            std::cin >> a >> b;

            rename_country(m_countries, a, b);
        }
        else if (op == "ABOUT")
        {
            std::string a;
            std::cin >> a;
            
            about(m_countries, a);
        }
        else if (op == "DUMP")
        {
            dump(m_countries);
        }
    }
    return 0;
}