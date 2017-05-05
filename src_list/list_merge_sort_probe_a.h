#pragma once

namespace junk
{
    namespace list_merge_sort_probe_a
    {
        class List
        {
            public:
                struct Node
                {
                    Node(int data) : data(data), next(nullptr){}
                    int data;
                    Node *next;
                };

            public:
                List() : m_head(nullptr){}
                ~List() { Clear(); }

                Node* head() { return m_head; }

                void Insert(Node *after, int data)
                {
                    if (!m_head){
                        m_head = new Node(data);
                    }
                    else
                    {
                        if (after == nullptr){
                            Node *new_node = new Node(data);
                            new_node->next = m_head;
                            m_head = new_node;
                        }
                        else
                        {
                            Node *iter = m_head;
                            while(iter)
                            {
                                if (iter == after){
                                    Node *next_next = iter->next;
                                    iter->next = new Node(data);
                                    iter->next->next = next_next;
                                }
                                iter = iter->next;
                            }
                        }
                    }
                }

                void MergeSort()
                {
                    if (m_head){
                        m_head = MergeSortImpl(m_head);
                    }
                }

                Node* MergeSortImpl(Node *head)
                {
                    if (!head->next){
                        return head;
                    }

                    Node *lhs = nullptr;
                    Node *rhs = nullptr;

                    SplitList(head, &lhs, &rhs);

                    lhs = MergeSortImpl(lhs);
                    rhs = MergeSortImpl(rhs);

                    return MergeLists(lhs, rhs);
                }

                void Clear()
                {
                    if (m_head)
                    {
                        Node *iter = m_head;
                        while(iter)
                        {
                            Node *next = iter->next;
                            delete iter;
                            iter = next;
                        }
                    }
                }
            private:
                void SplitList(Node *head, Node **lhs, Node **rhs)
                {
                    if (!head || !head->next) { // nothing to split
                        return; 
                    }

                    Node *slow = head;
                    Node *fast = head->next;

                    while (fast)
                    {
                        if (!fast->next){
                            break;
                        }
                        slow = slow->next;
                        fast = fast->next->next;
                    }

                    Node *slow_next = slow->next;
                    *rhs = slow_next;
                    slow->next = nullptr;
                    *lhs = head;
                }


                Node* MergeLists(Node *lhs, Node *rhs)
                {
                    if (!rhs){
                        return lhs; 
                    }else if (!lhs){
                        return rhs;
                    }
                
                    if (lhs->data <= rhs->data){
                        lhs->next = MergeLists(lhs->next, rhs);
                        return lhs;
                    }
                    
                    rhs->next = MergeLists(lhs, rhs->next);
                    return rhs;
                }

            private:
                Node *m_head;
        };
    }
}