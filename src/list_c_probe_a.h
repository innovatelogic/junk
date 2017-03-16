
namespace junk
{
	namespace list_c_probe_a
	{
		struct ListNode
		{
			ListNode(int val)
			: value(val)
			, next(nullptr){}
			int value;
			ListNode *next;
		};
		
		template<typename T>
		bool insertFront(T **head, T *new_node)
		{
			if (!head || !*head || !new_node){
				return false;
			}
			
			new_node->next = *head;
			*head = new_node;
			
			return true;
		}
		
		template<typename T>
		bool remove(T **head, T *del_elem)
		{
			if (!head || !*head || !del_elem){
				return false;
			}
			
			if (del_elem == *head)
			{
				T *next = (*head)->next;
				delete del_elem;
				*head = next;
				return true;
			}
			else
			{
				T *iter = *head;
				while (iter->next)
				{
					if (iter->next == del_elem)
					{
						T *next = iter->next->next;
						delete del_elem;
						iter->next = next;
						return true;
					}
				}
			}
			return false;
		}

        template<typename T>
        T* tail(T *head)
        {
            if (!head) {
                return nullptr;
            }

            T* iter = head;
            while (iter->next){
                iter = iter->next;
            }
            return iter;
        }

        template<typename T>
        size_t size(T *head)
        {
            size_t size = 0;
            T* iter = head;
            while (iter)
            {
                ++size;
                iter = iter->next;
            }
            return size;
        }

        template<typename T>
        void reverse(T **head)
        {
            if (!head || !*head) {
                return;
            }

            T *end = *head;
            T *iter = (*head)->next;

            while (iter)
            {
                T *next = iter->next;
                iter->next = end;
                end = iter;
                iter = next;
            }
            (*head)->next = nullptr;
            *head = end;
        }
	}
}