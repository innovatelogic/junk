#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <numeric>

void permutation_impl(const std::vector<int> &v, std::vector<bool> &flags, std::stack<int> &out)
{
    if (out.size() == v.size())
    {
        auto copy = out;

        std::vector<int> v_out;

        while (!copy.empty())
        {
            v_out.push_back(copy.top());
            copy.pop();
        }
        std::reverse(std::begin(v_out), std::end(v_out));
        for (int x : v_out) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
        return;
    }

    for (size_t i = 0; i < v.size(); ++i)
    {
        if (flags[i]){
            continue;
        }

        flags[i] = true;

        out.push(v[i]);

        permutation_impl(v, flags, out);

        out.pop();

        flags[i] = false;
    }
}

void permutation(int n)
{
    std::vector<int> v(n);
    std::vector<bool> flags(n);
    std::stack<int> out;

    for (int i = 0; i < n; i++)
    {
        v[i] = i + 1;
        flags[i] = false;
    }

    std::reverse(std::begin(v), std::end(v));


    permutation_impl(v, flags, out);
}


/*
int main() 
{
    int range_length;
    cin >> range_length;
    vector<int> permutation(range_length);

    // iota             -> http://ru.cppreference.com/w/cpp/algorithm/iota
    // Заполняет диапазон последовательно возрастающими значениями
    iota(permutation.begin(), permutation.end(), 1);

    // reverse          -> http://ru.cppreference.com/w/cpp/algorithm/reverse
    // Меняет порядок следования элементов в диапазоне на противоположный
    reverse(permutation.begin(), permutation.end());

    // prev_permutation ->
    //     http://ru.cppreference.com/w/cpp/algorithm/prev_permutation
    // Преобразует диапазон в предыдущую (лексикографически) перестановку,
    // если она существует, и возвращает true,
    // иначе (если не существует) - в последнюю (наибольшую) и возвращает false
    do {
    for (int num : permutation) {
        cout << num << ' ';
    }
    cout << endl;
    } while (prev_permutation(permutation.begin(), permutation.end()));

    return 0;
}
*/
int main()
{
    int n = 0;

    std::cin >> n;
    permutation(n);

    return 0;
}