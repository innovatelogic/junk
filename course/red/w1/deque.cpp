
#include <iostream>
#include <vector>

template<typename T>
class Deque
{
public:
    Deque()
    {}

    void PushFront(const T &v)
    {
        m_front.push_back(v);
    }

    void PushBack(const T &v)
    {
        m_back.push_back(v);
    }

    bool Empty() const { return m_front.empty() && m_back.empty(); }

    size_t Size() const { return m_front.size() + m_back.size(); }

    T& operator[](size_t index)
    {
        if (!m_front.empty() && index <= m_front.size() - 1){
            return m_front[m_front.size() - 1 - index];
        }
        else
        {
            size_t index_back = index - m_front.size();
            return m_back[index_back];
        }
    }

    const T& operator[](size_t index) const
    {
        if (!m_front.empty() && index <= m_front.size() - 1){
            return m_front[m_front.size() - 1 - index];
        }
        else
        {
            size_t index_back = index - m_front.size();
            return m_back[index_back];
        }
    }

    T& At(size_t index)
    {
        if (index >= Size()){
            throw std::out_of_range("");
        }
        return operator[](index);
    }

    const T& At(size_t index) const
    {
        if (index >= Size()){
            throw std::out_of_range("");
        }
        return operator[](index);
    }

    T& Front() { return operator[](0); }
    T& Back() { return operator[](Size() - 1); }

    const T& Front() const { return operator[](0); }
    const T& Back() const { return operator[](Size() - 1); }

protected:
private:
    typename std::vector<T> m_front;
    typename std::vector<T> m_back;
};
/*
void main()
{
    Deque<int> deq;
    deq.PushBack(1);
    deq.PushBack(2);
    deq.PushBack(3);
    deq.PushFront(0);
    deq.PushFront(-1);

    std::cout << deq.Front() << std::endl;
    //std::cout << deq.Back() << std::endl;
}*/