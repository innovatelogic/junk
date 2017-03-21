#pragma once

#include "defexport.h"

namespace junk
{
    namespace heap
    {
        template<class T>
        class JUNK_EXPORT heap
        {
            heap(const heap &source) = delete;
            heap& operator=(const heap &source) = delete;

        public:
            heap()
                : m_size(0)
                , m_last(-1)
                , m_heap(nullptr)
            {
                m_size = reallocate();
            }

            heap(const T *ptr, size_t n)
                : m_size(n)
                , m_heap(nullptr)
            {
                m_size = reallocate();
                memcpy(static_cast<void*>(m_heap), static_cast<const void*>(ptr), n * sizeof(T));
                m_last = n - 1;
            }

            heap::~heap()
            {
                delete[] m_heap;
            }

            const T* c_array() const { return m_heap; }
            int last() const { return m_last; }
            int size() const { return m_size; }

            void insert(const T &value)
            {
                if (m_last == m_size - 1) {
                    m_size = reallocate();
                }

                m_last += 1;
                m_heap[m_last] = value;

                insertImpl(m_last);
            }

            void build_maxheap()
            {
                const size_t actual_size = m_last + 1;
                for (int i = actual_size / 2; i >= 0; --i){
                    max_heapify(i, actual_size);
                }
            }

            size_t PARENT(size_t i) const { return (i - 1)  / 2; }
            size_t LEFT(int i) const { return i * 2 + 1; }
            size_t RIGHT(int i) const { return i * 2 + 2; }

            void max_heapify(int i, size_t len)
            {
                T &curr = m_heap[i];
                size_t l = LEFT(i);
                size_t r = RIGHT(i);

                int largest = i;
                if ((l < len) && m_heap[l] > curr){
                    largest = l;
                }
                if (r < len && m_heap[r] > m_heap[largest]){
                    largest = r;
                }

                if (largest != i)
                {
                    std::swap(curr, m_heap[largest]);
                    max_heapify(largest, len);
                }
            }
            
            void heap_sort()
            {
                build_maxheap();

                for (int i = m_last; i >= 0; --i)
                {
                    std::swap(m_heap[0], m_heap[i]);
                    max_heapify(0, i);
                    m_last--;
                }
            }

        private:
            size_t reallocate()
            {
                size_t size = m_size;

                if (!m_heap)
                {
                    size = (m_size == 0) ? 128 : m_size * 2;
                    m_heap = new T[size];
                }
                else
                {
                    const size_t new_size = size * 2;
                    T *new_heap = new T[new_size];
                    memcpy(static_cast<void*>(new_heap), static_cast<void*>(m_heap), size * sizeof(T));

                    delete[] m_heap;
                    m_heap = new_heap;

                    size = new_size;
                }
                return size;
            }

            void build_max_heap()
            {
                for (int i = m_last / 2; i >= 0; --i)
                {
                    max_heapify(i);
                }
            }

            void insertImpl(int index)
            {
                while (index)
                {
                    int parent = PARENT(index);

                    if (m_heap[parent] > m_heap[index])
                    {
                        std::swap(m_heap[parent], m_heap[index]);
                    }

                    index = parent;
                }
            }

        private:
            T *m_heap;
            size_t m_size;
            int m_last;
        };
    }
}