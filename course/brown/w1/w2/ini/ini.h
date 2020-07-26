#pragma once

#include <unordered_map>
#include <istream>
#include <string>

namespace Ini
{
using Section = std::unordered_map<std::string, std::string>;

class Document 
{
public:

Section& AddSection(std::string name)
{
    if (sections.count(name) == 0){
        auto ret = sections.insert(std::make_pair<std::string, Section>(std::move(name), {}));
        return ret.first->second;
    }
    return sections[name];
}

const Section& GetSection(const std::string& name) const
{
    return sections.at(name);
}

size_t SectionCount() const
{
    return sections.size();
}

private:
  std::unordered_map<std::string, Section> sections;
};


Document Load(std::istream& input)
{
    Document doc;

    Section *sect = nullptr;

    char ch;
    while (input >> ch)
    {
        if (ch == '[')
        {
            std::string name;
            std::getline(input, name);

            sect = &(doc.AddSection(name.substr(0, name.size() - 1)));

           // std::cout << "sect : [" << name << "]" << std::endl;

        }
       else if (ch == ' ')
        {
            continue;
        }
        else
        {
            std::string name;
            name += ch;
            for (char c; input >> c && c != '='; ) {
                name += c;
            }

            std::string value;
            input >> value;

            sect->insert({name, value});
           // std::cout << "val : [" << name << "] [" << value << "]" << std::endl;
        }
    }

    return doc;
}

}