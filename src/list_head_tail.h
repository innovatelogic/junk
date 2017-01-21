
#pragma once

#include "defexport.h"
#include <assert.h>

namespace junk
{
    template<class T>
    class JUNK_EXPORT list_node
    {
    public:
        list_node(const T &data)
            : m_next(nullptr)
            , m_data(data)
        {}

        ~list_node()
        {}

        list_node* next() { return m_next; }
        T& data() { return m_data; }

        void set_next(list_node *next) { m_next = next; }

    private:
        list_node *m_next;
        T m_data;
    };

    //----------------------------------------------------------------------------------------------
    //
    //----------------------------------------------------------------------------------------------

    template<class T, class T_NODE = list_node<T>>
    class JUNK_EXPORT list_tail
    {
    public:
        list_tail()
            : m_head(nullptr)
            , m_tail(nullptr)
        {}

        T_NODE* head() { return m_head; }
        T_NODE* tail() { return m_tail; }

        //----------------------------------------------------------------------------------------------
        bool insert(const T &data, T_NODE *after)
        {
            bool bResult = false;

            if (!m_head) // empty list case
            {
                assert(!after && !m_tail);
                m_head = m_tail = new T_NODE(data); // one element list head equal tail
                bResult = true;
            }
            else
            {
                if (m_head == m_tail) // one element list tail equal head
                {
                    if (!after) // insert to front
                    {
                        auto *new_node = new T_NODE(data);

                        new_node->set_next(m_head);

                        m_tail = m_head;

                        m_head = new_node;
                    }
                    else if (after == m_head)
                    {
                        auto *new_node = new T_NODE(data);

                        m_head->set_next(new_node);

                        m_tail = new_node;

                        bResult = true;
                    }
                }
                else // conventional insertion
                {
                    if (!after) // insertion into front (after == nullparam)
                    {
                        auto *new_node = new T_NODE(data);

                        new_node->set_next(new_node);

                        m_head = new_node;

                        bResult = true;
                    }
                    else if (after == m_tail) // insert after tail
                    {
                        auto *new_node = new T_NODE(data);

                        m_tail->set_next(new_node);

                        m_tail = new_node;

                        bResult = true;
                    }
                    else // mid insertion common case
                    {
                        auto *new_node = new T_NODE(data);

                        new_node->set_next(after->next());

                        after->set_next(new_node);

                        bResult = true;
                    }
                }
            }
            return bResult;
        }

        //----------------------------------------------------------------------------------------------
        bool erase(T_NODE *node)
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
            return bResult;
        }

    protected:
    private:
        T_NODE *m_head;
        T_NODE *m_tail;
    };
}
