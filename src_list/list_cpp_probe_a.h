
namespace junk
{
	namespace list_cpp_probe_a
	{
		struct ListNode
		{
			ListNode(int val)
			: value(val)
			, next(nullptr){}
			
			int value;
			ListNode *next;
		};
		
		class List
		{
		public:
			List()
			: m_head(nullptr)
            , m_tail(nullptr)
			{}
			
			~List(){
				clear();
			}
			
			ListNode* insert(ListNode *after, int value)
			{
				if (!after)
				{
					ListNode *new_element = new ListNode(value);
					new_element->next = m_head;
					m_head = new_element;
					
					if (!m_tail){
						m_tail = new_element;
					}
					return new_element;
				}
				else
				{
					ListNode *iter = m_head->next;
					
					while(iter)
					{
						if (iter == after)
						{
							ListNode *new_node = new ListNode(value);
							new_node->next = iter->next;
							iter->next = new_node;
							
							if (!new_node->next){
								m_tail = new_node;
							}
							return new_node;
						}

						iter = iter->next;
					}
				}
				return nullptr;
			}

            void clear()
            {
                ListNode *iter = m_head;
                while (iter)
                {
                    ListNode *next = iter->next;
                    delete iter;
                    iter = next;
                }
                m_head = m_tail = nullptr;
            }

            ListNode* head() { return m_head; }
            ListNode* tail() { return m_tail; }

		private:
			ListNode *m_head;
			ListNode *m_tail;
		};
	
	}
}