#include "junk.h"

#if 0
#include "find_list_Nth_from_end.h"
#include "permutations_array.h"
#include <iostream>

void main()
{
    std::cout << "Junk start" << std::endl;

    //junk::TestListNthFromEnd();

    //junk::print_permutations("abcd");
    
    const std::vector<char> arr = { 'A', 'B', 'C', 'D' };

    junk::permutate<char>(arr, [](const std::vector<char> &res) 
    {
        for (size_t i = 0; i < res.size(); ++i) {
            std::cout << res[i];
        }
        std::cout << std::endl;
    });

    int k = 0;
    std::cin >> k;

    std::cout << "Junk stop" << std::endl;
}
#endif