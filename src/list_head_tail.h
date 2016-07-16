#pragma once

#include <assert.h>

template<class T>
class ListNode final
{
public:
    ListNode(const T &data)
        : m_next(nullptr)
        , m_data(data)
    {}

    ~ListNode()
    {}

    ListNode* next() { return m_next; }
    T& data() { return m_data;  }

    void set_next(ListNode *next) { m_next = next; }
private:
    ListNode *m_next;
    T m_data;
};

//----------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------

template<class T>
class ListTail
{
public:
    ListTail()
        : m_head(nullptr)
        , m_tail(nullptr)
    {}

    ListNode<T>* head() { return m_head; }
    ListNode<T>* tail() { return m_tail; }
    //----------------------------------------------------------------------------------------------
    bool insert(const T &data, ListNode<T> *after)
    {
        bool bResult = false;

        if (!m_head) // empty list case
        {
            assert(!after && !m_tail);
            m_head = m_tail = new ListNode<T>(data); // one element list head equal tail
            bResult = true;
        }
        else
        {
            if (m_head == m_tail) // one element list tail equal head
            {
                if (!after) // insert to front
                {
                    auto *new_node = new ListNode<T>(data);

                    new_node->set_next(m_head);

                    m_tail = m_head;

                    m_head = new_node;
                }
                else if (after == m_head)
                {
                    auto *new_node = new ListNode<T>(data);

                    m_head->set_next(new_node);

                    m_tail = new_node;

                    bResult = true;
                }
            }
            else // conventional insertion
            {
                if (!after) // insertion into front (after == nullparam)
                {
                    auto *new_node = new ListNode<T>(data);

                    new_node->set_next(new_node);

                    m_head = new_node;

                    bResult = true;
                }
                else if (after == m_tail) // insert after tail
                {
                    auto *new_node = new ListNode<T>(data);

                    m_tail->set_next(new_node);

                    m_tail = new_node;

                    bResult = true;
                }
                else // mid insertion common case
                {
                    auto *new_node = new ListNode<T>(data);

                    new_node->set_next(after->next());

                    after->set_next(new_node);

                    bResult = true;
                }
            }
        }

        return bResult;
    }

    //----------------------------------------------------------------------------------------------
    bool erase(ListNode<T> *node)
    {
        bool bResult = false;

        if (!m_head || !node)
        {
            assert(!m_tail);
            return bResult;
        }

        if (node == m_head)
        {
            auto *new_head = m_head->next();

            delete node;

            m_head = new_head;

            if (!new_head) // delete last element
            {
                m_head = m_tail = nullptr;
            }
            bResult = true;
        }
        else
        {
            auto *iter = m_head;

            while (iter)
            {
                if (iter->next() == node)
                {
                    if (node == m_tail) // delete tail element
                    {
                        m_tail = iter;
                    }
                    iter->set_next(node->next());

                    delete node;

                    bResult = true;

                    break;
                }
                iter = iter->next();
            }
        }
    }

protected:
private:
    ListNode<T> *m_head;
    ListNode<T> *m_tail;
};

//----------------------------------------------------------------------------------------------
void TestListTail()
{
    ListTail<int> list;

    list.insert(2, nullptr); // 2
    list.insert(1, nullptr); // 1 2
    list.insert(22, list.tail());// 1 2 22
    list.insert(33, list.head());// 1 33 2 22

    list.erase(list.head()); // 33 2 22
    list.erase(list.tail()); // 33 2
    list.erase(list.head()->next()); // 2
    list.erase(list.head()); // null null
}