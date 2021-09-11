#include <iostream>
#include <functional>
#include <vector>
#include <cstddef>
#include <set>
#include <string>
#include <assert.h>


template<typename T>
void _union(typename std::vector<T>::iterator begin1, typename std::vector<T>::iterator end1,
            typename std::vector<T>::iterator begin2, typename std::vector<T>::iterator end2,
            typename std::vector<T> &out)
{
    while (begin1 != end1 && begin2 != end2)
    {
        if (*begin1 < *begin2)
        {
            out.push_back(*begin1);
            ++begin1;
        }
        else if (*begin2 < *begin1)
        {
            out.push_back(*begin2);
            ++begin2;
        }
        else
        {
            out.push_back(*begin1);
            ++begin1;
            ++begin2;
        }
    }

    for (auto it = begin1; it != end1; ++it){
        out.push_back(*it);
    }

    
    for (auto it = begin2; it != end2; ++it){
        out.push_back(*it);
    }
}

template<typename T>
void _intersection(typename std::vector<T>::iterator begin1, typename std::vector<T>::iterator &end1,
                   typename std::vector<T>::iterator begin2, typename std::vector<T>::iterator &end2,
                   typename std::vector<T> &out)
{
    while (begin1 != end1 && begin2 != end2)
    {
        if (*begin1 < *begin2){
            ++begin1;
        }
        else if (*begin2 < *begin1){
            ++begin2;
        }else
        {
            out.push_back(*begin1);
            ++begin1;
            ++begin2;
        }
    }
}

short parity0(int n)
{
    short k = 0;
    while (n)
    {
        k ^= n & 1;
        n >>= 1;
    }

    return k;
}

short parity1(int n)
{
    short k = 0;
    while (n) {
        k ^= 1;
        n &= n - 1;
    }
    return k;
}

class parity_cache
{
public:
    parity_cache(size_t n)
    : varray(n)
    {
        for (int i = 0; i < n; ++i) {
            varray[i] = parity1(i) == 1 ? true : false;
        }
    }

    bool operator[](size_t n) const { return varray[n]; }

public:
    std::vector<bool> varray;
};

short parity_check(int n)
{
    static parity_cache cache(1 << 8);

    return cache[n & 0xffffff00] ^
           cache[n & 0xffff00ff] ^
           cache[n & 0xff00ffff] ^
           cache[n & 0x00ffffff];
}

short parity_check_xor(unsigned long long n)
{
    assert(sizeof(unsigned long long) == 8);

    n ^= (n >> 32);
    n ^= (n >> 16);
    n ^= (n >> 8);
    n ^= (n >> 4);
    n ^= (n >> 2);
    n ^= (n >> 1);

    return n & 1;
}

unsigned long long swap_bits(unsigned long long v, size_t i, size_t j)
{
    unsigned long long m = (1l << i) | (1l << j);

    if ((v | m) == v) {
        return v;
    }

    return v ^ m;
}

unsigned int reverse_bits(unsigned int val)
{
    const int bits_size = sizeof(unsigned int) * 8;
    for (size_t i = 0; i < bits_size / 2; i++)
    {
        size_t j = bits_size - i - 1;

        if (((val >> i) & 1u) != ((val >> j) & 1u)){
            
            int mask = (1 << i) | (1 << j);
            val ^= mask;

        }
    }
    return val;
}

unsigned char reverse_bits_ch(unsigned char val)
{
    const int bits_size = sizeof(unsigned char) * 8;
    for (size_t i = 0; i < bits_size / 2; i++)
    {
        size_t j = bits_size - i - 1;

        if (((val >> i) & 1u) != ((val >> j) & 1u)){
            
            int mask = (1 << i) | (1 << j);
            val ^= mask;

        }
    }
    return val;
}

class reverse_lut
{
public:
    reverse_lut()
    : m_lut(1 << 8)
    {
        for (unsigned int i = 0; i < (1 << 8); i++)
        {
            m_lut[i] = reverse_bits_ch(i);
            //std::cout << m_lut[i] << " ";
        }
        std::cout << std::endl;
    }

    unsigned char operator[](unsigned int i) const { return m_lut[i]; }

private:
    std::vector<unsigned char> m_lut;
};

unsigned int reverse_bits_lut(unsigned int val)
{
    static reverse_lut lut;

    const size_t bits_n = 8;

    unsigned char bits[4] = {
        lut[(val >> (8 * 3)) & ((1 << 8) - 1)],
        lut[(val >> (8 * 2)) & ((1 << 8) - 1)],
        lut[(val >> 8) & ((1 << 8) - 1)],
        lut[val & ((1 << 8) - 1)],
    };

    //std::cout << lut[0] << " " << lut[1] << " " << lut[2] << " " << lut[3] << std::endl; 

    return unsigned int(bits[0]) | 
           unsigned int(bits[1] << 8) | 
           unsigned int(bits[2] << (8 * 2)) | 
           unsigned int(bits[3] << (8 * 3)); 
}

unsigned int find_closest_weight(unsigned int val)
{
    for (int i = 1; i < sizeof(unsigned int) * 8; ++i)
    {
        int j = i - 1;
        
        if (((val >> i) & 1) != ((val >> j) & 1)) 
        {
            //std::cout << i << " " << j << std::endl;
            unsigned int mask = (1 << i) | (1 << j);
            val ^= mask;
            break;
        }
    }
    return val;
}

unsigned int add(unsigned int a, unsigned int b)
{
    unsigned int carry = 0;
    unsigned int result = 0;

    for (int i = 0; i < sizeof(unsigned int) * 8; ++i)
    {
        result |= ((a & 1) ^ (b & 1) ^ carry) << i;
        carry = ((a & 1) & (b & 1)) | ((a & 1) & carry) | ((b & 1) & carry);

        a >>= 1;
        b >>= 1;
    }

    return result;
}

unsigned int mult(unsigned int x, unsigned int y)
{
    unsigned int sum = 0;

    while (x)
    {
        if (x & 1){
            sum = add(sum, y);
        }

        x >>= 1, y <<= 1;
    }
    return sum;
}


std::set<int> find_n_largest(const std::vector<int> &v, size_t n)
{
    std::set<int> elements;

    if (n == 0) {
        return elements;
    }

    elements.insert(v[0]);

    for (size_t i = 1; i < v.size(); ++i)
    {
        if (elements.size() < n || v[i] >= *elements.begin())
        {
            elements.insert(v[i]);

            if (elements.size() > n){
                elements.erase(elements.begin());
            }
        }
    }

    return elements;
}

int reverse_didgit(int value)
{
    int result = 0;

    bool positive = value > 0;
    if (!positive) {
        value = abs(value);
    }

    int v_copy = value;
    int count = 0;
    while(v_copy) {
        v_copy /= 10;
        ++count;
    }

    //std::cout << "count : " << count << std::endl;
    int div = 10;
    int inv_div = pow(10, count - 1);
    while (count)
    {
        int r = value % div;

        //std::cout << "r : " << r << std::endl;
        value -= r;

        result += (r / (div / 10)) * inv_div;

        --count;

        div *= 10;
        inv_div /= 10;
    }
    return result * (positive ? 1 : -1);
}

std::string _itoa(int v, int base)
{
    bool minus = v < 0;
    if (minus) { v *= -1; }

    std::string out;
    while (v)
    {
        std::cout << v % base << std::endl;
        out = "0123456789ABCDF"[v % base] + out;
        v /= base;
    }

    if (minus) {
        out = std::string("-") + out;
    }

    return out;
}

struct control_block
{
    control_block()
    : m_counter(1)
    {}

    size_t m_counter;
};

template<typename T>
class t_sptr
{
public:
    t_sptr()
    : m_ctr(new control_block)
    , m_data(nullptr) 
    {
        std::cout << "t_sptr default ctor : " << this << std::endl; 
    }

    t_sptr(const T &data)
    : m_ctr(new control_block)
    , m_data(new T(data))
    {
        std::cout << "t_sptr data ctor. :" << this << std::endl; 
    }

    t_sptr(T* pdata)
    : m_ctr(new control_block)
    , m_data(pdata)
    {
        std::cout << "t_sptr ptr ctor. : " << this << std::endl; 
    }

    /*t_sptr(T &&pd)
    {
       std::cout << "t_sptr move data ctor. : " << this << std::endl;
       m_ctr = new control_block; 
       m_data = pd;

       //&pd = nullptr;
    }*/

    t_sptr(t_sptr &&sp)
    {
       std::cout << "t_sptr move ctor." << std::endl;
       m_ctr = sp.m_ctr; 
       m_data = sp.m_data;

       sp.m_ctr = nullptr;
       sp.m_data = nullptr;
    }

    t_sptr(const t_sptr &other)
    {
        m_ctr = other.m_ctr;
        m_ctr->m_counter++;
        m_data = other.m_data;
    }

    ~t_sptr()
    {
        std::cout << "t_sptr dtor. : " << this << std::endl;
        release();
    }

    T* operator->()
    {
        return m_data;
    }

    T operator*()
    {
        return *m_data;
    }

    t_sptr& operator=(const t_sptr &other)
    {
        std::cout << "operator =" << std::endl;
        if (this != &other)
        {
            release();
            m_ctr = other.m_ctr;
            m_ctr->m_counter++;
            m_data = other.m_data;
        }
        else
        {
            std::cout << "skip self assign" << std::endl;
        }
        return *this;
    }

    t_sptr& operator=(const t_sptr &&other)
    {
        if (this != other)
        {
            release();
            m_ctr = std::move(other.m_ctr);
            m_data = std::move(other.m_data);
        }
    }

    void release()
    {
        if (m_ctr)
        {
            m_ctr->m_counter--;

            if (m_ctr->m_counter == 0)
            {
                delete m_data;
                m_data = 0;
            }
        }
    }

    void print()
    {
        std::cout << (!m_ctr ? "empty m_ctr" : "m_ctr valid") << " " <<
                     (!m_data ? "empty m_data" : "m_data valid") << std::endl;
    }
protected:

private:
    control_block *m_ctr;
    T *m_data;
};


class TestObj
{
public:
    TestObj(){
        std::cout << "ctor. TestObj : " << this << std::endl;
    }

    TestObj(const TestObj &other){
        std::cout << "copy ctor. TestObj : " << this << std::endl;
    }

    TestObj(TestObj &&other){
        std::cout << "move ctor. TestObj : " << this << std::endl;
    }

    ~TestObj(){
        std::cout << "dtor. TestObj : " << this << std::endl;
    }

    void foo(){
        std::cout << "foo : " << this << std::endl;
    }
};

struct list_node
{
    int data;
    list_node *next;
};

list_node* reverse_list(list_node *root)
{
    if (!root->next){
        return root;
    }

    list_node *l = root;
    list_node *n = root->next;

    while (n)
    {
        list_node *nn = n->next;

        std::cout << "l[" << l->data << "], n[" << n->data << "] nn[" << (nn ? std::to_string(nn->data) : "null") << "]" << std::endl;

        n->next = l;

        l = n;  

        n = nn;
    }

    root->next = nullptr;

    return l;
}

int main()
{
    std::vector<int> arr1{1, 2, 3};
    std::vector<int> arr2{0, 1, 2};

    {
        std::vector<int> out;
        _intersection<int>(arr1.begin(), arr1.end(),
                    arr2.begin(), arr2.end(),
                    out);

        for (auto n : out)
        {
            std::cout << n << " ";
        }
    }

    std::cout << std::endl;

    {
        std::vector<int> out;
        _union<int>(arr1.begin(), arr1.end(),
                    arr2.begin(), arr2.end(),
                    out);

        for (auto n : out)
        {
            std::cout << n << " ";
        }
    }

    std::cout << "parity" << std::endl;
    std::cout << parity0(0) << " " << parity1(0) << std::endl;
    std::cout << parity0(1) << " " << parity1(1) << std::endl;
    std::cout << parity0(2) << " " << parity1(2) << std::endl;
    std::cout << parity0(3) << " " << parity1(3) << std::endl;


    std::cout << "parity check" << std::endl;
    std::cout << parity_check(100) << std::endl;
    std::cout << parity_check(101) << std::endl;

    std::cout << "parity check xor" << std::endl;
    std::cout << parity_check_xor(100) << std::endl;
    std::cout << parity_check_xor(101) << std::endl;

    std::cout << "swap bits" << std::endl;
    std::cout << swap_bits(20, 4, 0) << std::endl;
    std::cout << swap_bits(20, 2, 0) << std::endl;
    std::cout << swap_bits(20, 2, 4) << std::endl;
    std::cout << swap_bits(73, 6, 1) << std::endl;

    int n = 0;
    int &ref = n;
    //int &ref_nc = 5;
    const int &ref_c = 5; 
    int &&rref = 5;

    std::cout << "reverse bits" << std::endl;

    std::cout << reverse_bits(5) << std::endl;
    std::cout << reverse_bits_lut(5) << std::endl;

    std::cout << "closest weight" << std::endl;
    std::cout << find_closest_weight(7) << std::endl;
    std::cout << find_closest_weight(13) << std::endl;


    std::cout << "sum" << std::endl;
    std::cout << add(171, 3) << std::endl;

    std::cout << "mult" << std::endl;
    std::cout << mult(13, 9) << std::endl;
    std::cout << mult(111, 9) << std::endl;


    std::cout << "find_n_largest" << std::endl;
    std::vector<int> arr{9, 4, 19, 18, 3, 5, 11};

    auto elements = find_n_largest(arr, 4);

    for (auto e : elements){
        std::cout << e << " ";
    }
    std::cout << std::endl;

    std::cout << "reverse_didgit" << std::endl;
    std::cout << reverse_didgit(1302) << std::endl;

    std::cout << "itoa" << std::endl;
    std::cout << _itoa(1456789, 10) << std::endl;
    std::cout << _itoa(-1456789, 10) << std::endl;

    {
        std::cout << "__sptr" << std::endl;
        //t_sptr<TestObj> sptr_inst;

        std::cout << "1" << std::endl;

        t_sptr<TestObj> sptr_inst2(new TestObj());

        std::cout << "2" << std::endl;

        //auto *p = new TestObj;
        //t_sptr<TestObj> sptr_inst_rv(std::move(*p));

        std::cout << "3" << std::endl;

        t_sptr<TestObj> sptr_inst_cpy = std::move(sptr_inst2);

        std::cout << "4" << std::endl;

        //sptr_inst = sptr_inst2;

        /*sptr_inst_cpy->foo();
        (*sptr_inst_cpy).foo();

        t_sptr<TestObj> sptr_inst_mov(std::move(sptr_inst));

        sptr_inst.print();
        sptr_inst_mov.print();

        sptr_inst_mov = sptr_inst_mov;

        sptr_inst2;*/
    }

    {
        std::cout << "rev list" << std::endl;

        list_node *root = new list_node{0, new list_node{1, new list_node{2, new list_node{3, nullptr}}}};

        list_node *p = root;
         while (p)
        {
            std::cout << p->data << " ";
            p = p->next;
        }

        std::cout << std::endl;

        list_node *new_root = reverse_list(root);

        while (new_root)
        {
            std::cout << new_root->data << " ";
            new_root = new_root->next;
        }
    }

    return 0;
}