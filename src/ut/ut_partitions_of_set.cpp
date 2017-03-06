#include "junk.h"
#include <gtest/gtest.h>


namespace junk
{
    namespace partitions_of_set
    {
       /* void printp(int *s, int n) 
        {
            // Get the total number of partitions. In the example above, 2.
            int part_num = 1;
            int i;
            for (i = 0; i < n; ++i)
            {
                if (s[i] > part_num) {
                    part_num = s[i];
                }
            }

            // Print the p partitions. 
            for (int p = part_num; p >= 1; --p) 
            {
                printf("{");
                // If s[i] == p, then i + 1 is part of the pth partition. 
                for (i = 0; i < n; ++i)
                {
                    if (s[i] == p)
                    {
                        printf("%d, ", i + 1);
                    }
                }
                printf("\b\b} ");
            }
            printf("\n");
        }

        
        //next
        //- given the partitioning scheme represented by s and m, generate
       // the next

       // Returns: 1, if a valid partitioning was found
       // 0, otherwise

        int next(int *s, int *m, int n)
        {
           // Update s: 1 1 1 1 -> 2 1 1 1 -> 1 2 1 1 -> 2 2 1 1 -> 3 2 1 1 ->
           // 1 1 2 1 ... 

            int i = 0;
            ++s[i];
            while ((i < n - 1) && (s[i] > m[i] + 1))
            {
                s[i] = 1;
                ++i;
                ++s[i];
            }

            // If i is has reached n-1 th element, then the last unique partitiong
            //has been found
            if (i == n - 1)
                return 0;

            // Because all the first i elements are now 1, s[i] (i + 1 th element)
            //is the largest. So we update max by copying it to all the first i
            //positions in m.
            int max = s[i];
            for (i = i - 1; i >= 0; --i)
            {
                m[i] = max;
            }
            return 1;
        }
        /
        TEST(Combinatorics, PartitionsOfSet)
        {
            int s[16]; // s[i] is the number of the set in which the i-th element should go 
            int m[16]; // m[i] is the largest of the first i elements in s

            int n = 4;
            int i;
            // The first way to partition a set is to put all the elements in the same
            //subset. 
            for (i = 0; i < n; ++i) {
                s[i] = 1;
                m[i] = 1;
            }

            // Print the first partitioning. 
            printp(s, n);

            // Print the other partitioning schemes. 
            while (next(s, m, n))
            {
                printp(s, n);
            }
        }*/


         int length;
        // This function takes "string", which contains a description
        // of what bits should be set in the output, and writes the
        // corresponding binary representation to the terminal.
        // The variable "position" is the effective last position.
        
        void output(int string[], int position)
        {
            int * temp_string = new int[length];
            std::vector<int> arr;
            int index = 0;
            int i;
            for (i = 0; i < length; i++)
            {
                if ((index < position) && (string[index] == i))
                {
                    temp_string[i] = 1;
                    arr.push_back(1);
                    index++;
                }
                else
                {
                    temp_string[i] = 0;
                    arr.push_back(0);
                }
                    

            }
            for (i = 0; i < length; i++)
                std::cout << temp_string[i];
            delete[] temp_string;
            std::cout << std::endl;

        }
        // Recursively generate the banker’s sequence.
        void generate(int string[], int position, int positions)
        {
            if (position < positions)
            {
                if (position == 0)
                {
                    for (int i = 0; i < length; i++)
                    {
                        string[position] = i;
                        generate(string, position + 1, positions);
                    }
                }
                else
                {
                    for (int i = string[position - 1] + 1; i < length; i++)
                    {
                        string[position] = i;
                        generate(string, position + 1, positions);
                        
                    }
                }
            }
            else
                output(string, positions);
        }
        // Main program accepts one parameter: the number of elements
        // in the set. It loops over the allowed number of ones, from
        // zero to n.       
        TEST(Combinatorics, PartitionsOfSet)
        {
            length = 4;
            for (int i = 0; i <= length; i++)
            {
                int * string = new int[length];
                generate(string, 0, i);
                delete[] string;
            }
        }
    }
}