#include <iostream>
#include <vector>
#include <string>

using t_queue = std::vector<bool>;

void worry_n(t_queue &v, int n)
{
    if (n >= 0 && n < v.size()){
        v[n] = true;
    }
}

void quiet_n(t_queue &v, int n)
{
    if (n >= 0 && n < v.size()){
        v[n] = false;
    }
}

void come_n(t_queue &v, int n)
{
    if (n > 0)
    {
        t_queue q_new(n, false);
        v.insert(end(v), begin(q_new), end(q_new));
    }
    else if (n < 0)
    {
        int left_n = v.size() - std::abs(n);

        if (left_n < 0){
            left_n = 0;
        }

        //std::cout << v.size() << " left: " << left_n << std::endl;
        v.erase(begin(v) + left_n, end(v));
    }
}

size_t worry_count(const t_queue &v)
{
    size_t count = 0;

    for (size_t i = 0; i < v.size(); ++i)
    {
        if (v[i]) {
            ++count;
        }
    }

    return count;
}

void print(const t_queue &v)
{
    for (size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout << '\n';
}

int main()
{
    size_t q = 0;
    std::cin >> q;

    t_queue queue;
    std::vector<size_t> worry;

    std::string op;
    int n;

    for (size_t i = 0; i < q; ++i)
    {
        std::cin >> op;

        if (op == "COME")
        {
            std::cin >> n;
            come_n(queue, n);
            //print(queue);
        }
        else if (op == "WORRY")
        {
            std::cin >> n;
            worry_n(queue, n);
            //print(queue);
        }
        else if (op == "QUIET")
        {
            std::cin >> n;
            quiet_n(queue, n);
            //print(queue);
        }
        else if (op == "WORRY_COUNT")
        {
            worry.push_back(worry_count(queue));
        }
    }

    for (int c : worry)
    {
        std::cout << c << std::endl;
    }
}