#pragma once

namespace junk
{
    namespace list_reverse_from_nth
    {       
        struct node
        {
            node()
            : next(nullptr)
            {}
            int data;
            node *next;
        };

        template<typename>
        class list
        {
            public:
                list()
                : m_head(nullptr){}

                ~list(){ clear(); }

                node* head() { return m_head; }

                void push_back(int data)
                {
                    if (!m_head)
                    {
                        m_head = new node();
                        m_head->data = data;
                    }
                    else
                    {
                        node *iter = m_head;
                        while(iter->next)
                        {
                            iter = iter->next;
                        }
                        iter->next = new node();
                        iter->next->data = data;
                    }
                }

                void clear()
                {
                    node *iter = m_head;
                    while (iter)
                    {
                        node * iter_next = iter->next;
                        delete iter;
                        iter = iter_next;
                    }
                }

                void reverse_from(int data)
                {
                    if (m_head)
                    {
                        node *start = m_head;
                        node *prev = nullptr;

                        while (start)
                        {
                            if (start->data == data){
                                break;
                            }
                            prev = start;
                            start = start->next;
                        };

                        if (prev && !prev->next)
                        {
                            return; // nothing to reverse. return
                        }
                        else
                        {
                            node *end = prev ? prev->next : m_head;
                            node *last = end;

                            node *walker = end->next;
                            node *walker_prev = nullptr;

                            while (walker)
                            {
                                node *iter_next = walker->next;

                                walker->next = end;

                                end = walker;

                                walker = iter_next;
                            }

                            last->next = nullptr;

                            if (prev)
                            {
                                prev->next = end;
                            }
                            else{
                                m_head = end;
                            }
                        }
                    }
                }
            protected:
            private:
                node *m_head;
        };
    }
}