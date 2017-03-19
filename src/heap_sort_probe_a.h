
namespace junk
{
	namespace heap_sort_probe_a
	{
		class Heap
		{
			Heap(const Heap &source) = delete;
			
		public:
			Heap()
			: m_size(0)
			, m_last(-1){
				m_size = reallocate();
			}
			
			~Heap(){
				delete m_heap;
			}
			
			void insert(int value)
			{
				if (m_last == m_size - 1){
					m_size = reallocate();
				}
				
				m_heap[++m_last] = value;
				insert_impl(m_last);
			}
			
			static int LEFT(int i) { return i * 2 + 1;}
			static int RIGHT(int i) { return i * 2 + 2; }
			static int PARENT(int i) { return i / 2; }
			
			void build_max_heap()
			{
				int len = m_last + 1;
				
				for (int i = len / 2; i >= 0; i--)
				{
					max_heapify(i, len);
				}
			}
			
			void max_heapify(int i, int len)
			{
				int largest = i;
				
				int lhs = LEFT(i);
				if (lhs < len && m_heap[lhs] > m_heap[i])
				{
					largest = lhs;
				}
				int rhs = RIGHT(i);
				if (rhs < len && m_heap[rhs] > m_heap[largest])
				{
					largest = rhs;
				}
				
				if (i != largest)
				{
					std::swap(m_heap[i], m_heap[largest]);
					max_heapify(largest, len);
				}
			}
			
			void heap_sort()
			{
				while (m_last > 0)
				{
					std::swap(m_heap[0], m_heap[m_last--]);
					
					max_heapify(0, m_last + 1);
				}
			}
			
			int* array() const { return m_heap; }
			int last() const { return m_last; }
			int size() const { return m_size; }
			
		protected:
		private:
		
			void insert_impl(int i)
			{
				if (i == 0){
					return;
				}
				
				int parent = PARENT(i);
				
				if (m_heap[i] > m_heap[parent])
				{
					std::swap(m_heap[i], m_heap[parent]);
					insert_impl(parent);
				}
			}
		
			int reallocate()
			{
				int size = m_size;
				
				if (size == 0)
				{
					size = (size == 0) ? 127 : size;
					m_heap = new int[size];
				}
				else
				{
					size = (size * 2) + 1;
					int *tmp_heap = new int[size];
					memcpy(static_cast<void*>(tmp_heap), static_cast<void*>(m_heap), sizeof(m_heap) * sizeof(int));
					delete m_heap;
					m_heap = tmp_heap;
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
