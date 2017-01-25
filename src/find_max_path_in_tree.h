#include "defexport.h"
#include <vector>
#include <string>

namespace junk
{
    namespace dfs_tree
    {
        struct JUNK_EXPORT ValueNode
        {
            std::string *name;
            size_t value;
            std::vector<ValueNode*> *childs;

            ValueNode(std::string &name_, size_t val_)
                : value(val_)
            {
                name = new std::string(name_);
                childs = new std::vector<ValueNode*>();
            }

            ~ValueNode()
            {
                delete name;
                delete childs;
            }
        };

        template<class T = ValueNode>
        class JUNK_EXPORT TreeDFS
        {
        public:
            TreeDFS(T *root)
                : m_root(root)
                , m_max(0)
                , m_crumbles(new std::list<T*>())
                , m_crumbles_max(new std::list<T*>())
            {}

            ~TreeDFS()
            {
                delete m_crumbles;
                delete m_crumbles_max;
            }

            size_t FindMaxPath()
            {
                m_max = 0;

                FindMaxImpl(m_root, 0);
                
                return m_max;
            }

        protected:
            void FindMaxImpl(T *node, size_t value)
            {
                if (node->childs->empty())
                {
                    if (value > m_max)
                    {
                        m_max = value;
                        *m_crumbles_max = *m_crumbles;
                    }
                    return;
                }

                m_crumbles->push_back(node);

                std::vector<T*>::iterator end = node->childs->end();
                for (std::vector<T*>::iterator iter = node->childs->begin(); 
                    end != iter; ++iter)
                {    
                    FindMaxImpl(*iter, value + (*iter)->value);
                }
                
                m_crumbles->pop_back();
            }

        private:
            T *m_root;
            size_t m_max;

            std::list<T*> *m_crumbles;
            std::list<T*> *m_crumbles_max;
        };
    }
}