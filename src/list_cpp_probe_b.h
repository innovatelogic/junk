
namespace junk
{
	namespace list_cpp_probe_b
	{
		struct Node
		{
			Node(int val)
			: value(val)
			, next(nullptr)
			, rand(nullptr){}
			
			int value;
			Node *next;
			Node *rand;
		};
		
		class List
		{
		public:
			List()
			: m_head(nullptr)
			, m_tail(nullptr){}
			
			List(const List &source)
			{
				if (this != &source)
				{
					//deep_copy(source);
				}
			}
			
			~List() { clear(); }
			
			void insert(Node *after, int value)
			{
				if (after == nullptr)
				{
					Node *new_node = new Node(value);
					new_node->next = m_head;
					
					if (!m_tail){
						m_tail = new_node;
					}
					
					m_head = new_node;
				}
				else
				{
					Node *iter = m_head;
					
					while (iter)
					{
						if (iter == after)
						{
							Node *new_node = new Node(value);
							new_node->next = iter->next;
							
							iter->next = new_node;
							
							if (!(new_node->next)){
								m_tail = new_node;
							}
							break;
						}
						iter = iter->next;
					}
				}
			}
			
			void clear()
			{
				Node *iter = m_head;
				
				while (iter)
				{
					Node *next = iter->next;
					
					delete iter;
					
					iter = next;
				}
				
				m_head = m_tail = nullptr;
			}
			
			const Node* head() const { return m_head; }
            const Node* tail() const { return m_tail; }

            Node* head() { return m_head; }
            Node* tail() { return m_tail; }
			
			void deep_copy(List &source)
			{
				clear();
				
				Node *iter = source.head();
				
				while(iter)
				{
                    Node *new_node = new Node(iter->value);
                    new_node->next = iter->next;
					iter->next = new_node;
					iter = iter->next->next;
				}
				
				iter = source.head();
				while (iter)
				{
					if (iter->rand){
						iter->next->rand = iter->rand->next;
					}
					iter = iter->next->next;
				}
				
				iter = source.head();
				while (iter)
				{
					Node *next_src = iter->next->next;
					
					if (!m_head){
						m_head = m_tail = iter->next;
					}
					else
					{
						m_tail->next = iter->next;
						m_tail = iter->next;
					}
	
					iter->next = next_src;
					iter = next_src;
				}
				
			}
			
		protected:
		
		private:
			Node *m_head;
			Node *m_tail;
		};
	}
}