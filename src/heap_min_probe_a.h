#pragma once 
#include <limits.h>

namespace junk
{
	namespace heap_min_probe_a
	{
		class HeapMin
		{
			public:
			HeapMin()
			: m_heap(nullptr)
			, m_last(-1)
			, m_size(0)
			{ m_size = reallocate();}
			
			~HeapMin() { delete m_heap;}
			
			void insert(int value)
			{
				if (m_last == m_size - 1){
					m_size = reallocate();
				}
				m_heap[++m_last] = value;
				insert_impl(m_last);
			}
			
			void increase_min(int val)
			{
				if (!m_heap){
					return;
				}
				
				m_heap[0] += val;
				min_heapify(0, m_last + 1);
			}

            int min()
            {
                int min = INT_MIN;
                if (m_heap && m_last >= 0) {
                    min = m_heap[0];
                }
                return min;
            }

            int max()
            {
                int max = INT_MIN;
                if (m_heap && m_last >= 0)
                {
                    max = m_heap[0];
                    for (int i = 1; i < m_last + 1; ++i) {
                        if (m_heap[i] > max) {
                            max = m_heap[i];
                        }
                    }
                }
                return max;
            }

			static int LEFT(int i) { return 2 * i + 1; }
			static int RIGHT(int i) { return 2 * i + 2; }
			static int PARENT(int i) { return (i - 1) / 2; }
			
			protected:
				void min_heapify(int i, int len)
				{
					int lowest = i;
					
					int lhs = LEFT(i);
					if (lhs < len && m_heap[lhs] < m_heap[i]){
						lowest = lhs;
					}
					
					int rhs = RIGHT(i);
					if (rhs < len && m_heap[rhs] < m_heap[lowest]) {
						lowest = lhs;
					}
					
					if (i != lowest)
					{
						std::swap(m_heap[i], m_heap[lowest]);
						min_heapify(lowest, len);
					}
				}
				
				void insert_impl(int i)
				{
					if (i == 0){
						return;
					}
					int parent = PARENT(i);
					if (m_heap[parent] > m_heap[i])
					{
						std::swap(m_heap[parent], m_heap[i]);
						insert_impl(parent);
					}
				}
			
				int reallocate()
				{
					int size = m_size;
					
					if (!m_heap)
					{
						size = m_size == 0 ? 127 : m_size;
						m_heap = new int [size];
					}
					else
					{
						size = size * 2 + 1;
						int *new_alloc = new int[size];
						memcpy(static_cast<void*>(new_alloc), static_cast<void*>(m_heap), sizeof(m_heap) * sizeof(int));
						delete m_heap;
						m_heap = new_alloc;
					}
					return size;
				}
			private:
				int *m_heap;
				int m_size;
				int m_last;
        };
	}
}