#include "../list_head_tail.h"
#include "../list_linearize.h"
#include <iostream>
#include <gtest/gtest.h>

namespace junk
{
    template<class T>
    class list_node_ex
    {
    public:
        list_node_ex(const T &data) 
            : m_next(nullptr)
            , m_prev(nullptr)
            , m_child(nullptr)
            , m_data(data)
        {}

        ~list_node_ex()
        {}

        list_node_ex* next() { return m_next; }
        T& data() { return m_data; }

        void set_next(list_node_ex *next) { m_next = next; }

        list_node_ex* prev() { return m_prev; }
        void set_prev(list_node_ex *ptr) { m_prev = ptr; }

        list_node_ex* child() { return m_child; }
        void set_child(list_node_ex *ptr) { m_child = ptr; }

    private:
        list_node_ex<T> *m_next;
        list_node_ex<T> *m_prev;
        list_node_ex<T> *m_child;
        
        T m_data;
    };

    TEST(list_tail, ListInsertRemoveTest)
    {
        list_tail<int> list;

        list.insert(2, nullptr); // 2
        list.insert(1, nullptr); // 1 2
        list.insert(22, list.tail());// 1 2 22
        list.insert(33, list.head());// 1 33 2 22

        list.erase(list.head()); // 33 2 22
        list.erase(list.tail()); // 33 2
        list.erase(list.head()->next()); // 2
        list.erase(list.head()); // null null
    }

    //----------------------------------------------------------------------------------------------
    TEST(list_tail, ListLinearizeTest)
    {
        //list_tail<int, list_node_ex<int>> list;

        typedef list_node_ex<int> N;

        // row 0
        N *r00 = new N(0);
        N *r01; r00->set_next(r01 = new N(1)); r01->set_prev(r00);
        N *r02; r01->set_next(r02 = new N(2)); r02->set_prev(r01);
        N *r03; r02->set_next(r03 = new N(3)); r03->set_prev(r02);
        N *r04; r03->set_next(r04 = new N(4)); r04->set_prev(r03);
            
        // row 1
        N* r10; r00->set_child(r10 = new N(5));
        N *r11; r10->set_next(r11 = new N(6)); r11->set_prev(r10);
        N *r12; r11->set_next(r12 = new N(7)); r12->set_prev(r11);

        N *r13; r03->set_child(r13 = new N(8)); 
        N *r14; r13->set_next(r14 = new N(9)); r14->set_prev(r13);

        // row 3
        N *r20; r11->set_child(r20 = new N(10));
        N *r21; r13->set_child(r21 = new N(11));

        N *head = r00;
        N *tail = r04;

        flatten_list<list_node_ex<int>>(head, &tail);

        int n = 0;
        N *curr = head;
        while (curr)
        {
            EXPECT_EQ(curr->data(), n);
            curr = curr->next();
            n++;
        }

        curr = head;
        while (curr->next())
        {
            N *tmp = curr->next();
            delete curr;
            curr = tmp;
        }
    }
}