#pragma once

#include "defexport.h"
#include <map>

namespace junk
{
    namespace heap_chart
    {
        template<typename T>
        class JUNK_EXPORT heap
        {
            heap(const heap&) = delete;
            heap& operator=(const heap&) = delete;

        public:
            heap()
                : m_heap(nullptr)
                , m_size(0)
                , m_last(-1)
            {
                m_size = reallocate();
            }

            heap(const T *ptr, size_t size)
                : m_size(size)
                , m_heap(nullptr)
            {
                m_size = reallocate();
                memcpy(static_cast<void*>(m_heap), static_cast<const void*>(ptr), size * sizeof(T));
                m_last = size - 1;
            }

            ~heap()
            {
                delete []m_heap;
            }

            size_t PARENT(size_t i) const { return i / 2; }
            size_t LEFT(size_t i) const { return i * 2 + 1; }
            size_t RIGHT(size_t i) const { return i * 2 + 2; }

            void insert(const T&value)
            {
                if (m_last == m_size - 1) {
                    m_size = reallocate();
                }

                m_last++;
                m_heap[m_last] = value;

                insertImpl(m_last);
            }

            void build_max_heap()
            {
                const size_t actual_size = m_last + 1;
                for (int i = actual_size / 2; i >= 0; i--) {
                    max_heapify(i, actual_size);
                }
            }

            void max_heapify(size_t index, size_t len)
            {
                T &curr = m_heap[index];
                size_t l = LEFT(index);
                size_t r = RIGHT(index);

                size_t largest = index;
                if ((l < len) && curr < m_heap[l]){
                    largest = l;
                }
                if (r < len && m_heap[largest] < m_heap[r]) {
                    largest = r;
                }

                if (largest != index)
                {
                    std::swap(curr, m_heap[largest]);
                    max_heapify(largest, len);
                }
            }

            size_t size() const { return m_size; }
            size_t last() const { return m_last; }
            T* data() const { return m_heap; }

        protected:
        private:
            int reallocate()
            {
                int size = m_size;

                if (!m_heap)
                {
                    size = (m_size == 0) ? 128 : m_size;
                    m_heap = new T[size];
                }
                else
                {
                    const size_t new_size = m_size * 2;
                    T *new_heap = new T[new_size];
                    memcpy(static_cast<void*>(new_heap), static_cast<void*>(m_heap), m_size * sizeof(T));
                    delete[] m_heap;
                    m_heap = new_heap;

                    size = new_size;
                }
                return size;
            }

            void insertImpl(size_t index)
            {
                while (index)
                {
                    size_t parent = PARENT(index);

                    if (m_heap[parent] < m_heap[index])
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

        class Chart
        {
        public:
            struct Record
            {
                std::string name;
                size_t rate;

                Record()
                    : name()
                    , rate(0) {}

                Record(const std::string &_name)
                    : name(_name)
                    , rate(1){}

                void incRate() { rate++; }

                bool operator < (const Record &other)
                {
                    return rate < other.rate;
                }
            };

            using TChart = std::map<std::string, heap<Record>*>;

            Chart()
            {}

            ~Chart()
            {
                for each (auto &item in m_chart){
                    delete item.second;
                }
            }

            void PlaySong(const std::string &author, const std::string &name)
            {
                TChart::const_iterator iter_find = m_chart.find(author);
                if (iter_find == m_chart.end()) {
                    m_chart.insert(std::make_pair(author, new heap<Record>()));
                }

                bool bFind = false;
                Record *pdata = m_chart[author]->data();
                int len = m_chart[author]->last();

                for (int i = 0; i <= len; i++)
                {
                    if (pdata[i].name == name)
                    {
                        pdata[i].incRate();

                        m_chart[author]->build_max_heap();

                        bFind = true;
                        break;
                    }
                }

                if (!bFind) {
                    m_chart[author]->insert(Record(name));
                }
            }

            std::string TopSong(const std::string &author)
            {
                std::string out;

                TChart::const_iterator iter_find = m_chart.find(author);
                if (iter_find != m_chart.end())
                {
                    if (m_chart[author]->last() >= 0)
                    {
                        out = m_chart[author]->data()[0].name;
                    }
                }
                return out;
            }

        protected:
        private:
            TChart m_chart;
        };
    }
}

