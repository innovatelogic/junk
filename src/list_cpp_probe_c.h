#pragma once
#include <vector>

namespace junk
{
    namespace list_cpp_probe_c
    {
        /*
            arrayA = [12, 24, 8, 32]
            arrayB = [13, 25, 32, 11]

            Push each number into sorted list sequence and mark element
            by mask which array it belongs to.
            (A, B, both or 0. 0 means element yet used).

            For instance:
            elements: 32 -> 25 -> 24 -> 13 -> 12 -> 11 -> 8
            mask:     ab    b     a     b     a     b     a 

            shuffling goes from left to right.
            * if element belongs to B array we can do nothing but connect
            most right A element and remove corresponding masks. (32 - 8)
            
            * if element belongs to A array we take closest right B element (32 - 25) end mark element as used.

            * move to next unused element.

            linear time if using double linked list but O(n) aux space.
        */
        const int MASK_A = 1;
        const int MASK_B = 2;

        struct Node
        {
            Node(int v, unsigned int m)
                : value(v)
                , mask(m)
                , next(nullptr) {}
            int value;
            unsigned int mask; // array's mask or both. 0- means item not used
            Node *next;
        };

        class List
        {
        public:
            List()
                : m_head(nullptr) {}

            ~List() { clear(); }

            void insert_value(int value, unsigned int mask)
            {
                if (!m_head) {
                    insert_after(nullptr, value, mask);
                }
                else
                {
                    Node *iter = m_head;
                    Node *p = nullptr;
                    while (iter)
                    {
                        if (value > iter->value) {
                            break;
                        }
                        else if (value == iter->value)
                        {
                            iter->mask |= mask;
                            return;
                        }
                        p = iter;
                        iter = iter->next;
                    }
                    insert_after(p, value, mask);
                }
            }

            void insert_after(Node *after, int value, unsigned int mask)
            {
                if (!m_head) {
                    m_head = new Node(value, mask);
                }
                else
                {
                    if (!after)
                    {
                        Node *new_node = new Node(value, mask);
                        new_node->next = m_head;
                        m_head = new_node;
                        return;
                    }

                    Node *iter = m_head;
                    while (iter)
                    {
                        if (iter == after)
                        {
                            Node *new_node = new Node(value, mask);
                            new_node->next = iter->next;
                            iter->next = new_node;
                            break;
                        }
                        iter = iter->next;
                    }
                }
            }

            void shuffle(std::vector<int> &outA, std::vector<int> &outB)
            {
                Node *iter = m_head;
                while (iter)
                {
                    if (iter->mask & MASK_B) // B-array
                    {
                        outB.push_back(iter->value);

                        // find most right A object
                        Node *i = iter->next;
                        Node *r = nullptr;

                        while (i)
                        {
                            if (i->mask & 1) { // object belongs to A-array
                                r = i;
                            }
                            i = i->next;
                        }
                        assert(r);

                        outA.push_back(r->value);

                        // clear masks
                        iter->mask &= ~MASK_B;
                        r->mask &= ~MASK_A;
                    }

                    if (iter->mask & MASK_A) // A-array
                    {
                        outA.push_back(iter->value);

                        // find closest right B-object
                        Node *i = iter->next;
                        while (i)
                        {
                            if (i->mask & MASK_B) {
                                break;
                            }
                        }

                        assert(i);
                        outB.push_back(i->value);

                        iter->mask &= ~MASK_A;
                        i->mask &= ~MASK_B;
                    }

                    iter = iter->next;
                }
            }

            void clear()
            {
                Node *iter = m_head;
                while (iter)
                {
                    Node *next = iter->next;
                    delete iter;
                    iter = next;
                }
            }

        protected:
            Node *m_head;
        };
    }
}