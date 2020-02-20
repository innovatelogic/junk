#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <initializer_list>

class Person
{
public:

    Person()
    {}

    void ChangeFirstName(int year, const std::string& first_name)
    {
        m_first_name_change[year] = first_name;
    }
    
    void ChangeLastName(int year, const std::string& last_name)
    {
        m_second_name_change[year] = last_name;
    }

    std::string GetName(const std::map<int, std::string> &cont, int year) const
    {
        std::string out;

        if (cont.empty()){
            return out;
        }

        auto low = cont.upper_bound(year);
        if (low != cont.begin()){
            low = std::prev(low);
        }

        if (low->first <= year){
            out = low->second;
        }

        return out;
    }

    std::string GetFullName(int year) const
    {
        std::string out;

        std::string first_name = GetName(m_first_name_change, year);
        std::string last_name = GetName(m_second_name_change, year);

        if (first_name.empty() && last_name.empty()){
           out = "Incognito";
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

private:
    std::map<int, std::string> m_first_name_change;
    std::map<int, std::string> m_second_name_change;
};


int main()
{
    //    Incognito
    //    Polina with unknown last name
    //    Polina Sergeeva
    //    Polina Sergeeva
    //    Appolinaria Sergeeva
    //    Polina Volkova
    //    Appolinaria Volkova

    Person person;

    person.ChangeFirstName(1965, "Polina");
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
    }
    return 0;
}
