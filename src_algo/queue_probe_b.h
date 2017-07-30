#pragma once

namespace junk
{
	namespace queue_probe_b
	{
		template<typename T>
		struct Node
		{
			Node(T &value):value(value), next(nullptr){}
			T value;
			Node *next;
		};
		template<typename T>
		class Queue
		{
			public:
				Queue() : m_head(nullptr), m_tail(nullptr){}
				~Queue() { clear();}
				
				void push(T &&value)
				{
					if (!m_tail)
					{
						m_head = m_tail = new Node<T>(value);
					}
					else
					{
						Node<T> *new_node = new Node<T>(value);
						m_tail->next = new_node;
						m_tail = new_node;
					}
				}
				
				void pop()
				{
					if (m_head)
					{
						Node<T> *next = m_head->next;
						delete m_head;
						m_head = next;
						if (!m_head){
							m_tail = nullptr;
						}
					}
				}
				
                Node<T>* front() { return m_head; }

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
				
			private:
				Node<T> *m_head;
				Node<T> *m_tail;
        };
	}
}