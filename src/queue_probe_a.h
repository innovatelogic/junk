#pragma once

namespace junk
{
	namespace queue_probe_a
	{
		template<typename T>
		struct Node
		{
			Node(T &value)
			: value(value), next(nullptr), prev(nullptr)
			{}
			T value;
			Node *next;
			Node *prev;
		};
		
		template<typename T>
		class Queue
		{
			public:
				Queue(): m_head(nullptr), m_tail(nullptr){}
				~Queue() { clear(); }
				
				void push(T &&val)
				{
					if (!m_head)
					{
						m_head = m_tail = new Node<T>(val);
					}
					else
					{
						Node<T> *new_node = new Node<T>(val);
						new_node->next = m_head;
						m_head->prev = new_node;
						m_head = new_node;
					}
				}
				
				void pop()
				{
					if (m_tail)
					{
						Node<T> *prev = m_tail->prev;
						delete m_tail;
						
						if (prev){
							m_tail = prev;
						}
						else{
							m_head = m_tail = nullptr;
						}
					}
				}
				
				Node<T>* front() { return m_tail; }
				
				void clear()
				{
					Node<T> *iter = m_head;
					while (iter)
					{
						Node<T> *next = iter->next;
						delete iter;
						iter = next;
					}
					m_head = m_tail = nullptr;
				}
				
			protected:
			private:
				Node<T> *m_head;
				Node<T> *m_tail;
		};
	}
}