#pragma once

namespace junk
{
	namespace dlist_probe_a
	{		
		struct node
		{
			node(char data)
			: data(data)
			, next(nullptr)
			, prev(nullptr)
			{}
			
			char data;
			node *next;
			node *prev;
		};
		
		class list
		{
			public:
				list()
				: m_head(nullptr)
				, m_tail(nullptr)
				{}
				
				~list() { clear(); }
				
				void insert(node *after, char val)
				{
					if (!m_head) // empty list
					{
						m_head = m_tail = new node(val);
					}
					else
					{
						if (m_head == m_tail) // one element size
						{
							if (after == nullptr)
							{
								node *new_node = new node(val);
								new_node->next = m_head;
								m_head->prev = new_node;
								m_head = new_node;
							}
							else if (after == m_head)
							{
								node *new_node = new node(val);
								new_node->prev = m_head;
								m_head->next = new_node;
								m_tail = new_node;
							}
						}
						else // 2 < size
						{
							node *new_node = new node(val);
								
							if (after == nullptr) // insert instead of head
							{
								m_head->prev = new_node;
								new_node->next = m_head;
								m_head = new_node;
							}
							else if (after == m_tail)
							{
								m_tail->next = new_node;
								new_node->prev = m_tail;
								m_tail = new_node;
							}
							else
							{
								node *after_next = after->next;
								
								after->next = new_node;
								new_node->prev = after;
								
								new_node->next = after_next;
								after_next->prev = new_node;
							}	
						}
					}
				}

                node* head() { return m_head; }
                node* tail() { return m_tail; }
				
			protected:
				void clear()
				{
					node * iter = m_head;
					
					while (iter)
					{
						node *iter_next = iter->next;
						
						delete iter;
						
						iter = iter_next;
					}
				}
			private:
				node *m_head;
				node *m_tail;
		};
	}
}