#include <iostream>
#include <vector>



std::vector<int> mult(const std::vector<int> &v1, const std::vector<int> &v2)
{
    std::vector<int> out;

    int index_start = 0;

    for (auto r_v2 = v2.rbegin(); r_v2 != v2.rend(); ++r_v2)
    {
        int index_n = index_start;

        int carry = 0;

        for (auto r_v1 = v1.rbegin(); r_v1 != v1.rend(); ++r_v1)
        {
            int val = (*r_v2) * (*r_v1);

            if (out.size() == index_n)
            {

                out.insert(out.begin(), val + carry);

                carry /= 10;

                if (*(out.begin()) >= 10)
                {
                    carry += *(out.begin()) / 10;
                    *(out.begin()) %= 10;
                }
            }
            else
            {
                *(out.end() - 1 - index_n) += val + carry;

                carry /= 10;

                if (*(out.end() - 1 - index_n) >= 10)
                {
                    carry += *(out.end() - 1 - index_n) / 10;
                    *(out.end() - 1 - index_n) %= 10;
                }

              
            }

            ++index_n;
        }

        if (carry != 0){
             out.insert(out.begin(), carry);
        }

        ++index_start;
    }

    return out;
}

int main()
{

    //auto res = mult({1, 2, 3}, {2, 2});

    auto res = mult({2, 9, 9}, {8, 8});

    for (int v : res)
    {
        std::cout << v;
    }
    return 0;
}