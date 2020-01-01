#include <iostream>
#include <string>
#include <fstream>

int main()
{
    const std::string input = "input.txt";
    const std::string output = "output.txt";


    std::ifstream in(input);
    std::ofstream out(output);

    if (in && out)
    {
        std::string line;
        while (getline(in, line))
        {
            //std::cout << line << std::endl;
            out << line << std::endl;
        }
    }

    return 0;
}