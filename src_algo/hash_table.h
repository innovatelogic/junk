#pragma once

#include "defexport.h"
#include <string>

namespace junk
{
    namespace hash_table
    {
        template<typename T_KEY, typename T_VALUE>
        struct Node
        {
            const T_KEY   key;
            T_VALUE value;
            Node *next;

            Node(const T_KEY &_key, T_VALUE &_value)
                : key(_key)
                , value(_value)
                , next(nullptr)
            {}
        };

        template<typename T_KEY, typename T_VALUE>
        class UniqueList
        {
        public:
            UniqueList()
                : m_head(nullptr)
                , m_size(0)
            {}

            ~UniqueList()
            {
                Clear();
            }

            void AddItem(const T_KEY &key, T_VALUE &value)
            {
                if (m_head == nullptr) {
                    m_head = new Node<T_KEY, T_VALUE>(key, value);
                    return;
                }

                Node<T_KEY, T_VALUE> *iter = m_head->next;
                Node<T_KEY, T_VALUE> *prev = m_head;
                while (iter)
                {
                    if (iter->key == key) {
                        iter->value = value;
                        return;
                    }

                    prev = iter;
                    iter = iter->next;
                }

                prev->next = new Node<T_KEY, T_VALUE>(key, value);
                m_size++;
            }

            void Remove(const T_KEY &key)
            {
                if (m_head)
                {
                    if (m_head->key == key) // remove head case
                    {
                        Node<T_KEY, T_VALUE> *next = m_head->next;
                        delete m_head;
                        m_head = next;
                        m_size--;
                    }
                    else
                    {
                        Node<T_KEY, T_VALUE> *iter = m_head->next;
                        Node<T_KEY, T_VALUE> *prev = m_head;

                        while (iter)
                        {
                            if (iter->key == key)
                            {
                                Node<T_KEY, T_VALUE> *next = iter->next;
                                delete iter;
                                prev->next = next;
                                m_size--;
                                return;
                            }

                            prev = iter;
                            iter = iter->next;
                        }
                    }
                }
            }

            const T_VALUE* GetValue(const T_KEY &key) const
            {
                T_VALUE *out = nullptr;

                Node<T_KEY, T_VALUE> *iter = m_head;
                while (iter)
                {
                    if (iter->key == key)
                    {
                        out = &iter->value;
                        break;
                    }
                }
                return out;
            }

            void Clear()
            {
                Node<T_KEY, T_VALUE> *iter = m_head;

                while (iter)
                {
                    Node<T_KEY, T_VALUE> *next = iter->next;
                    delete iter;
                    iter = next;
                }

                m_head = nullptr;
                m_size = 0;
            }

        public:
            Node<T_KEY, T_VALUE> *m_head;
            size_t m_size;
        };

        template<typename T_KEY, typename T_VALUE>
        class JUNK_EXPORT HashTable
        {
        public:
            HashTable(size_t length = 13)
            {
                if (length == 0) {
                    length = 13;
                }
                m_array = new UniqueList<T_KEY, T_VALUE>[length]();
                m_length = length;
            }

            ~HashTable()
            {
                delete[] m_array;
            }

            void Insert(const T_KEY &key, T_VALUE &value)
            {
                size_t _hash = hash(key);
                m_array[_hash]->AddItem(key, value);
            }

            void Insert(const T_KEY &key, T_VALUE value)
            {
                m_array[hash(key)].AddItem(key, value);
            }

            void Remove(const T_KEY &key)
            {
                m_array[hash(key)].Remove(key);
            }

            const T_VALUE* getItem(const T_KEY &key)
            {
                return m_array[hash(key)].GetValue(key);
            }

            size_t length() const { return m_length; }

            size_t hash(const T_KEY &key)
            {
                size_t hash = 0;
                for (size_t i = 0; i < key.length(); ++i)
                {
                    hash += (int)key[i];
                }
                return hash % m_length;
            }

        protected:
        private:
            UniqueList<T_KEY, T_VALUE> *m_array;
            size_t m_length;
        };
    }
}