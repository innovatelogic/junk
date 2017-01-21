#pragma once

#include "defexport.h"

template<class T>
class JUNK_EXPORT StackElement
{
public:
    StackElement(const T &data)
        : m_next(nullptr)
        , m_data(data)
    {}

    const T& data() const { return data; }
    T& data() { return data; }

    void setNext(StackElement *next) { m_next = next; }
    StackElement* next() { return m_next; }

protected:
private:
    StackElement *m_next;
    T m_data;
};

//----------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------
template<class T>
class JUNK_EXPORT Stack
{
public:
    Stack()
        : m_head(nullptr)
    {}

    //----------------------------------------------------------------------------------------------
    virtual ~Stack()
    {
        clear();
    }

    //----------------------------------------------------------------------------------------------
    ListElement<T>* top() { return m_head; }

    //----------------------------------------------------------------------------------------------
    bool push(const T &data)
    {
        bool bResult = false;
        if (!m_head)
        {
            m_head = new StackElement<T>(data); // check alloc

            bResult = true;
        }
        else
        {
            StackElement<T> *new_element = new StackElement<T>(data); // check alloc
            new_element->setNext(m_head);
            m_head = new_element;
        }
        return true;
    }

    //----------------------------------------------------------------------------------------------
    bool pop()
    {
        if (!m_head)
        {
            return false;
        }

        StackElement<T>* next = m_head->next();
        delete m_head;
        m_head = next;

        return true;
    }

    //----------------------------------------------------------------------------------------------
    void clear()
    {
        StackElement<T> *iter = m_head;
        while (iter)
        {
            StackElement<T> *next = iter->next();

            delete iter;

            iter = next;
        }

        m_head = nullptr;
    }
protected:
private:
    StackElement<T> *m_head;
};

//----------------------------------------------------------------------------------------------
void TestStack()
{
    Stack<int> stk;

    stk.push(1);
    stk.push(2);
    stk.push(3);

    // Ensure 3-2-1

    stk.pop();

    // ensure 2-1

    stk.pop();

    // ensure 1

    stk.push(4);

    // ensure 4-1

    stk.pop();
    stk.pop();

    // ensure empty

    stk.push(11);
    stk.push(22);
    stk.push(33);

    // ensure 33-22-11

    stk.clear();
    // ensure empty
}
