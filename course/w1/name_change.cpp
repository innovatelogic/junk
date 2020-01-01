#include <iostream>
#include <map>
#include <string>
#include <vector>


struct name_change
{
    std::string first_name;
    std::string last_name;
};

class Person
{
public:
    Person(const std::string &first, const std::string &second, int year)
    {
        m_name_change[year].first_name = first;
        m_name_change[year].last_name = second;
        m_birth_year = year;
    }


    void ChangeFirstName(int year, const std::string& first_name)
    {
        if (year >= m_birth_year) {
            m_name_change[year].first_name = first_name;
        }
    }
    
    void ChangeLastName(int year, const std::string& last_name)
    {
        if (year >= m_birth_year) {
            m_name_change[year].last_name = last_name;
        }
    }

    std::string GetFullName(int year) const
    {
        std::string out;

        std::string first_name;
        std::string last_name;

        for (const auto &it : m_name_change)
        {
            if (it.first <= year)
            {
                if (!it.second.first_name.empty()){
                    first_name = it.second.first_name;
                }

                if (!it.second.last_name.empty()){
                    last_name = it.second.last_name;
                }
            }
            else{
                break;
            }
        }

        if (first_name.empty() && last_name.empty()){
           out = "No person";
        }
        else if (first_name.empty() && !last_name.empty()){
            out = last_name + " with unknown first name";
        }
        else if (!first_name.empty() && last_name.empty()){
           out = first_name + " with unknown last name";
        }
        else{
            out = first_name + " " + last_name;
        }

        return out;
    }

    std::string GetFullNameWithHistory(int year) const
    {
        std::string out;

        std::string first_name;
        std::string last_name;

        std::vector<std::string> h_first_name, h_last_name;

        for (const auto &it : m_name_change)
        {
            if (it.first <= year)
            {
                if (!it.second.first_name.empty())
                {
                    first_name = it.second.first_name;

                    if (h_first_name.empty() || *(h_first_name.rbegin()) != first_name){
                        h_first_name.push_back(first_name);
                    }
                }

                if (!it.second.last_name.empty())
                {
                    last_name = it.second.last_name;

                    if (h_last_name.empty() || *(h_last_name.rbegin()) != last_name){
                        h_last_name.push_back(last_name);
                    }
                }
            }
            else {
                break;
            }
        }

        if (first_name.empty() && last_name.empty()){
           out = "No person";
        }
        else if (first_name.empty() && !last_name.empty())
        {
            std::string h_l = print_history(h_last_name);
            out = last_name + (!h_l.empty() ? " " + h_l : "") + " with unknown first name";
        }
        else if (!first_name.empty() && last_name.empty())
        {
            std::string h_f = print_history(h_first_name);
            out = first_name + (!h_f.empty() ? " " + h_f : "") + " with unknown last name";
        }
        else {
            std::string h_l = print_history(h_last_name);
            std::string h_f = print_history(h_first_name);

            out = first_name + (!h_f.empty() ? (" " + h_f + " ") : " ")  + last_name + (!h_l.empty() ? " " + h_l : "");
        }

        return out;
    }

private:
    std::string print_history(const std::vector<std::string> &h) const
    {
        std::string out;

        const size_t sz = h.size() - 1;
        const size_t last = sz - 1;
        for (int i = last; i >= 0; --i)
        {
            out += h[i] + (i != 0 ? ", " : "");
        }

        return !out.empty() ? (std::string("(") + out + ")") : "";
    }

private:
    std::map<int, name_change> m_name_change;
    int m_birth_year;
};

int main()
{
    //Person person;
  
    /*person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        std::cout << person.GetFullName(year) << std::endl;
    }
    
    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        std::cout << person.GetFullName(year) << std::endl;
    }
    
    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        std::cout << person.GetFullName(year) << std::endl;
    }*/

    /*person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        std::cout << person.GetFullNameWithHistory(year) << std::endl;
    }
  

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
    std::cout << person.GetFullNameWithHistory(year) << std::endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
    std::cout << person.GetFullNameWithHistory(year) <<std:: endl;
    }

    person.ChangeFirstName(1990, "Polina");
    person.ChangeLastName(1990, "Volkova-Sergeeva");
    std::cout << person.GetFullNameWithHistory(1990) << std::endl;

    person.ChangeFirstName(1966, "Pauline");
    std::cout << person.GetFullNameWithHistory(1966) << std::endl;

    person.ChangeLastName(1960, "Sergeeva");
    for (int year : {1960, 1967}) {
    std::cout << person.GetFullNameWithHistory(year) << std::endl;
    }

    person.ChangeLastName(1961, "Ivanova");
    std::cout << person.GetFullNameWithHistory(1967) << std::endl;*/

    Person person("Polina", "Sergeeva", 1960);
    for (int year : {1959, 1960}) {
        std::cout << person.GetFullNameWithHistory(year) << std::endl;
    }

    person.ChangeFirstName(1965, "Appolinaria");
    person.ChangeLastName(1967, "Ivanova");
    for (int year : {1965, 1967}) {
        std::cout << person.GetFullNameWithHistory(year) << std::endl;
    }
    return 0;
}