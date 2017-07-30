

#pragma once

namespace junk
{
    namespace rotate_list_kth_element
    {
        template<typename T>
        struct Node
        {
            T value;
            Node *next;

            Node(const T &val)
                : value(val)
                , next(nullptr)
            {}
        };

        template<typename T>
        class JUNK_EXPORT List
        {
        public:
            List()
                : m_head(nullptr)
                , m_len(0)
            {}

            ~List()
            {
                Node<T> *iter = m_head;
                while (iter)
                {
                    Node<T> *next = iter->next;
                    delete iter;
                    iter = next;
                }
            }

            void Insert(const T value)
            {
                if (!m_head)
                {
                    m_head = new Node<T>(value);
                    m_len++;
                }
                else
                {
                    Node<T> *iter = m_head->next;
                    Node<T> *prev = m_head;

                    while (iter)
                    {
                        prev = iter;
                        iter = iter->next;
                    }

                    prev->next = new Node<T>(value);
                    m_len++;
                }
            }

            void RotateOn(size_t k)
            {
                size_t mod_k = k % m_len;

                if (m_head && mod_k > 0)
                {
                    // localize new end of a list
                    Node<T> *iter_kth = m_head;
                    for (size_t i = 0; i < mod_k - 1; i++){
                        iter_kth = iter_kth->next;
                    }

                    // get current end-node
                    Node<T> *iter = iter_kth->next;
                    Node<T> *end = iter_kth;
                    while (iter)
                    {
                        end = iter;
                        iter = iter->next;
                    }

                    // rearrange list nodes
                    Node<T> *new_head = iter_kth->next;
                    iter_kth->next = nullptr;

                    end->next = m_head;
                    m_head = new_head;
                }
            }

            const Node<T>* head() const { return m_head; }

        protected:
        private:
            Node<T> *m_head;
            size_t m_len;
        };
    }
}