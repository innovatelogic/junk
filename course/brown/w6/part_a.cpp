#include <iostream>
#include <string>
#include <vector>
#include <istream>
#include <string_view>

using real_t = float;

struct Point
{
    real_t lattitude;
    real_t longitude;
};

struct Stop
{
    std::string name;
    Point point;
};

using t_string = std::string_view;

std::vector<t_string> tokenize(t_string str, t_string delim)
{
    //std::cout << "tokenize:[" << str << "]" << std::endl;

    std::vector<t_string> out;

    size_t pos = 0;
    size_t pos_next = str.find_first_of(delim);

    while (pos_next != std::string::npos)
    {
        t_string token = str.substr(pos, pos_next - pos);

        //std::cout << "[" << token << "]" << " [" << pos << " " << pos_next << "]" << std::endl;

        if (!token.empty()){
            out.push_back(token);
        }

        pos = pos_next + 1;
        pos_next = str.find_first_of(delim, pos);
    }

    t_string last = str.substr(pos);
    if (!last.empty()) {
        out.push_back(last);
    }

    return std::move(out);
}

void process_input_bus()
{
    std::string query;
    std::getline(std::cin, query);

    std::string_view q(query);

    auto pos_begin = q.find_first_not_of(" ");
    auto pos_delim = q.find_first_of(":");

    t_string number = q.substr(pos_begin, pos_delim - pos_begin);
    auto tokens = tokenize(q.substr(pos_delim + 1), " ,");

    std::cout << number << std::endl;
    for (const auto &t : tokens)
    {
        std::cout << t << std::endl;
    }

}

void process_input_stop()
{
    std::string query;
    std::getline(std::cin, query);

    std::string_view q(query);

    auto pos_begin = q.find_first_not_of(" ");
    auto pos_delim = q.find_first_of(":");

    std::cout << q << " "  << pos_begin << " " << pos_delim << std::endl;

    t_string name = q.substr(pos_begin, pos_delim - pos_begin);
    auto tokens = tokenize(q.substr(pos_delim + 1), " ,");

    std::cout << name << std::endl;
    for (const auto &t : tokens)
    {
        std::cout << t << std::endl;
    }
}

void process_input()
{
    size_t num;
    std::cin >> num;

    for (size_t idx = 0; idx < num; ++idx)
    {
        std::string name;
        std::cin >> name;

        if (name == "Bus") {
            process_input_bus();
        }
        else if (name == "Stop") {
            process_input_stop();
        }
    }
}

int main()
{
    process_input();
    return 0;
}