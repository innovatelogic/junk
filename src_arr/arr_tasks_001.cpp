#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

void even_odd_classify(std::vector<int> &arr)
{
    if (arr.size() <= 1){
        return;
    }

    int i = 0;
    int j = arr.size() - 1;

    while (i < j)
    {
        if (arr[i] % 2 == 0)
        {
            i++;
            continue;
        }
        else if (arr[j] % 2 != 0)
        {
            j--;
            continue;
        }

        std::swap(arr[i], arr[j]);
        i++;
        j--;
    }
}

void partitioning(std::vector<int> &arr, size_t pivot)
{
    size_t i = 0;
    size_t j = arr.size() - 1;

    while (i < j)
    {
        if (arr[i] <= arr[pivot])
        {
            std::swap(arr[i], arr[pivot]);
            pivot = i;
            i++;
        }
        else if (arr[i] > arr[j])
        {
            std::swap(arr[i], arr[j]);
        }
        else
        {
            j--;
        }
    }
}

void partitioning2(std::vector<int> &arr, size_t p)
{
    int pivot = arr[p];

    int i = 0;
    int j = arr.size() - 1;

    while (i < j)
    {
        if (arr[i] > pivot)
        {
            std::swap(arr[i], arr[j--]);
        }
        else if (arr[j] < pivot)
        {
            std::swap(arr[i++], arr[j]);
        }
        else
        {
            i++;
            j--;
        }
    }
}

void partitioning_n2(std::vector<int> &arr, size_t pivot)
{
    for (size_t i = 0; i < arr.size(); ++i)
    {
        for (size_t j = i + 1; j < arr.size(); ++j)
        {
            if (arr[j] < arr[i] && arr[j] < arr[pivot])
            {
                std::swap(arr[i], arr[j]);
                break;
            }
        }
    }

    for (int i = arr.size() - 1; i >= 0; i--)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[j] > arr[i]) {
                std::swap(arr[j], arr[i]);
                break;
            }
        }
    }
}

void partitioning_inv(std::vector<int> &arr, size_t pivot)
{
    const int P = arr[pivot];

    int smaller = 0, equal = 0, larger = arr.size();

    while (equal < larger)
    {
        if (arr[equal] < P)
        {
            std::swap(arr[equal++], arr[smaller++]);
        }
        else if (arr[equal] == P)
        {
            equal++;
        }
        else
        {
            std::swap(arr[--larger], arr[equal]);
        }
    }
}


void increment_value(std::vector<int> &arr)
{
    if (arr.empty()) { 
        arr.emplace_back(1); 
        return; 
    }

    arr.back()++;

    for (int i = arr.size() - 1; i > 0; --i)
    {
        if (arr[i] == 10){
            arr[i] = 0;
            arr[i - 1]++;
        }
    }

    if (arr[0] == 10)
    {
        arr[0] = 0;
        arr.insert(arr.begin(), 1);
    }
}

std::vector<int> mult(std::vector<int> v1, std::vector<int> v2)
{
    const int sign = (v1.front() > 0) ^ (v2.front() > 0) ? -1 : 1;

    v1[0] = std::abs(v1[0]); v2[0] = std::abs(v2[0]);

    int carry = 0;
    int res = 0;

    for (int i = v2.size() - 1, k = 1; i >= 0; --i)
    {
        int r = 0;
        for (int j = v1.size() - 1, d = 1; j >= 0; --j)
        {
            int k = v2[i] * v1[j] + carry;

            r += (k % 10) * d;

            carry = (k % 10) > 10 ? 1 : 0;

            d *= 10;
        }

        res += r * k;
        k *= 10;
    }  

    std::cout << res << std::endl;

    return {};
}


int reverse(int value)
{
    int out = 0;

    int sign = value > 0 ? -1 : 1;

    value = abs(value);

    int k = 1;
    while (value)
    {
        out = (out * 10) + value % 10;
        value /= 10;
    }

    return out * sign;
}

std::string reverse_string(std::string str)
{
    int i = 0;
    int j = str.length() - 1;

    while (j > i) {
        std::swap(str[i++], str[j--]);
    }
    return str;
}

class ctrl_block
{
public:
    ctrl_block()
    : m_count(1)
    {}

    int count() const { return m_count; }
    int inc() { return ++m_count; }
    int dec() { return --m_count; }

protected:
private:
    int m_count;
};

template<typename T>
class sptr_
{
public:
    sptr_()
    : m_ctr(new ctrl_block)
    , m_ptr(nullptr)
    {
        std::cout << "_sptr::ctor()\n";
    }

    sptr_(typename T *ptr)
    : m_ctr(new ctrl_block)
    , m_ptr(ptr)
    {
        std::cout << "_sptr ctor(T*)\n";
    }

    sptr_(typename T v)
    : m_ctr(new ctrl_block)
    , m_ptr(new T(v))
    {
        std::cout << "_sptr::ctor(T)\n";
    }

    sptr_(sptr_ &&other) noexcept
    {
        std::cout << "_sptr::ctor(&&)\n";

        m_ctr = std::exchange(other.m_ctr, nullptr);
        m_ptr = std::exchange(other.m_ptr, nullptr);
    }

    sptr_& operator=(const sptr_ &other)
    {
        if (&other == this) {std::cout << "prevent self copy\n"; return }

        release();

        m_ctr = other.m_ctr;
        m_ptr = other.m_ptr;

        m_ctr->inc();
    }

    sptr_& operator=(sptr_ &&other) noexcept
    {
        std::cout << "_sptr::operator=(&&)\n";

        if (&other == this) { std::cout << "prevent self move\n"; return *this; }
        release();

        m_ctr = std::exchange(other.m_ctr, nullptr);
        m_ptr = std::exchange(other.m_ptr, nullptr);

        return *this;
    }

    ~sptr_()
    {
        std::cout << "_sptr::dtor.\n";
        release();
    }

protected:
    void release()
    {
        if (m_ctr)
        {
            if (m_ctr->dec() == 0)
            {
                std::cout << "_sptr::release data. " << m_ptr << std::endl;
                delete m_ctr;
                delete m_ptr;

                m_ptr = nullptr;
                m_ctr = nullptr;
            }
        }
    }

private:
    T *m_ptr;
    ctrl_block *m_ctr;
};


struct A
{
    int a;
    int b;
    int c;

    A(int a, int b, int c) : a(a), b(b), c(c) { std::cout << "A::ctor.\n"; }
    ~A(){ std::cout << "A::dtor.\n"; }
};

unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

int str_to_int(const std::string &str)
{
    int out = 0;

    for (int i = 0; i < str.length(); i++)
    {
        int didgit = str[i] - '0';

        out = (out * 10) + didgit;
    }
    return out;
}

int main()
{
    {
        std::vector<int> arr{1, 11, 13, 2, 3, 4, 5, 14, 17};
        even_odd_classify(arr);

        for (auto n : arr)
        {
            std::cout << n << " ";
        }
        std::cout << '\n';
    }

    {
        std::cout << "partitioning \n";

        std::vector<int> arr{5, 4, 8, 4, 6, 3, 2, 4, 0, 1, 0};
        partitioning_inv(arr, 7);

        for (auto n : arr)
        {
            std::cout << n << " ";
        }
    }

    {
        std::cout << "\npartitioning_n2\n";

        std::vector<int> arr{5, 4, 8, 6, 7, 3, 2, 0, 1, 0};
        partitioning_n2(arr, 5);

        for (auto n : arr)
        {
            std::cout << n << " ";
        }
    }

    {
        std::cout << "\n increment" << std::endl;

        std::vector<int> arr{9, 9, 9};
        increment_value(arr);

        for (auto n : arr){
            std::cout << n << " ";
        }
    }

    {
        std::cout << "\n mult" << std::endl;
        mult({1, 2, 9}, {1, 2});
    }

    {
        std::cout << "\n mult" << std::endl;
        std::cout << reverse(123) << std::endl;
    }

    {
        std::cout << "\n strev" << std::endl;
        std::cout << reverse_string("abcdef") << std::endl;
        std::cout << reverse_string("abc") << std::endl;
    }


    {
        std::cout << "\n sptr" << std::endl;

        /*
        sptr_<int> ptr; // empty
        {
            sptr_<int> ptr2(1); // empty
            ptr = std::move(ptr2);

            
        }*/

        sptr_<int> ptr(std::move(sptr_<int>(1)));

    }

    {
        std::cout << "placement\n";

        char *buf = new char[sizeof(A)];

        A *p = new (buf) A(1, 2, 3);

        p->~A();

        std::cout << p->a << " " << p->b << " " << p->c << "\n";
        delete [] buf;
    }

    {
        std::cout << "str_to_didgit\n";
        std::cout << str_to_int("123") << std::endl;
    }
}