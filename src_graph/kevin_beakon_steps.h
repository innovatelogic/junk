#pragma once

#include "defexport.h"
#include <string.h>
#include <vector>
#include <map>
#include <list>
#include <algorithm>

namespace junk
{
    namespace kevin_beakon
    {
        template<class T>
        class JUNK_EXPORT Graph
        {
        public:
            typename typedef std::map<T, std::vector<T> >   TMap;
            typename typedef TMap::iterator                 TMapIter;
            typename typedef TMap::const_iterator           TMapConstIter;

        
            Graph()
                : m_linkmap(new TMap())
                , m_visited(new std::vector<T>())
                , m_crumbles(new std::map<T, T>())
            {}

            ~Graph()
            {
                delete m_linkmap;
                delete m_visited;
                delete m_crumbles;
            }

            bool AddNode(T node, const std::vector<T> links)
            {
                bool res = false;
                if (m_linkmap->find(node) == m_linkmap->end())
                {
                    (*m_linkmap)[node] = links;
                    res = true;
                }
                return res;
            }

            bool FindShortest(T a, const T b, int &count)
            {
                bool res = false;

                TMapIter iter_a = m_linkmap->find(a);
                TMapConstIter iter_b = m_linkmap->find(b);
                
                count = 0;

                m_visited->clear();
                m_crumbles->clear();

                if (iter_a != m_linkmap->end() && 
                    iter_b != m_linkmap->end())
                {
                    res = FindImpl(iter_a, iter_b, count);
                }
                return res;
            }

            void Trace(T b, std::list<T> &out)
            {
                out.clear();

                T &iter_val = b;

                std::map<T, T>::iterator iter_find = m_crumbles->find(iter_val);

                while (iter_find != m_crumbles->end())
                {
                    out.insert(out.begin(), iter_find->first);

                    if (iter_find->first == iter_find->second) {
                        break;
                    }
                    iter_find = m_crumbles->find(iter_find->second);
                }
            }

        protected:
            bool FindImpl(TMapIter &a, TMapConstIter &b, int &count)
            {
                std::vector<TMapIter> rim;
                std::vector<TMapIter> new_rim;

                rim.push_back(a);

                m_crumbles->insert(std::map<T, T>::value_type(a->first, a->first));

                while (!rim.empty())
                {
                    for each (auto &r in rim)
                    {
                        if (r->first == b->first){
                            return true;
                        }

                        m_visited->push_back(r->first);

                        std::vector<T> &linq = r->second;
                        for each (auto &next in linq)
                        {
                            if (std::find(m_visited->begin(), m_visited->end(), next) != m_visited->end()){
                                continue;
                            }

                            TMapIter iter_next = m_linkmap->find(next);
                            if (iter_next != m_linkmap->end())
                            {
                                m_crumbles->insert(std::map<T, T>::value_type(iter_next->first, r->first));
                                new_rim.push_back(iter_next);
                            }
                        }
                    }
                    count++;
                    rim = new_rim;
                }
                return false;
            }

        
           
        private:
            TMap *m_linkmap;

            std::vector<T> *m_visited;
            std::map<T, T> *m_crumbles;
        };
    }
}