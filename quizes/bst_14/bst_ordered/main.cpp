#include <iostream>
#include <assert.h>

struct node
{
    node(int data)
    : data(data)
    {}

    int data;
    node *lhs;
    node *rhs;
};


class bst
{
public:
    bst()
    : m_root(nullptr)
    {}

    ~bst()
    {
        delete m_root;
    }

    node* insert(int data)
    {
        if (!m_root) {
            m_root = new node(data);
            return m_root;
        }
        else
        {
            node *curr = m_root;

            while(1)
            {
                // lhs
                if (data < curr->data)
                {
                    if (!curr->lhs){
                        curr->lhs = new node(data);
                        return curr->lhs;
                    }
                    else{
                        curr = curr->lhs;
                    }
                }
                else // rhs
                {
                    if (!curr->rhs)
                    {
                        curr->rhs = new node(data);
                        return curr->rhs;
                    }
                    else
                    {
                        curr = curr->rhs;
                    }
                }
            };
        }
        assert(false);
    }

    bst& add(int data)
    {
        insert(data);
        return *this;
    }

    bool pair_include_ancestor_and_descendant_of_m(node *possible_anc_or_desc_0,
                                                   node *possible_anc_or_desc_1,
                                                   node *mid)
    {
        auto *search_0 = possible_anc_or_desc_0;
        auto *search_1 = possible_anc_or_desc_1;

        while ( search_0 != possible_anc_or_desc_1 && 
                search_1 != possible_anc_or_desc_0 &&
                search_0 != mid &&
                search_1 != mid &&
                (search_0 || search_1))
        {
            if (search_0)
            {
                search_0 = mid->data < search_0->data ? search_0->lhs : search_0->rhs; 
            }

            if (search_1)
            {
                search_1 = mid->data < search_1->data ? search_1->lhs : search_1->rhs;
            }
        }


        if ((search_0 != mid && search_1 != mid) || 
            search_0 == possible_anc_or_desc_1 ||
            search_1 == possible_anc_or_desc_0)
            {
                return false;
            }

        if (search_0 == mid)
        {
            return is_descendant(mid, possible_anc_or_desc_1);
        }
        else // search_1 == mid
        {
            return is_descendant(mid, possible_anc_or_desc_0);
        }
    }


    bool is_descendant(node *root, node *find)
    {
        assert(root && find);

        while (root)
        {
            if (root == find){
                return true;
            }

            root = find->data < root->data ? root->lhs : root->rhs;
        }
        return false;
    }

//private:
    node *m_root;
};



int main()
{
    // chpt. 14 p.243
    bst _bst;

    _bst.add(19).add(7).add(43).add(3).add(11).add(23).add(47).add(2).add(5).add(17).add(37).add(53).add(13).add(29).add(41).add(41).add(31);


    {
        // true
        auto *I = _bst.m_root->rhs;
        auto *L = _bst.m_root->rhs->lhs->rhs->lhs;
        auto *K = _bst.m_root->rhs->lhs->rhs;

        std::cout << _bst.pair_include_ancestor_and_descendant_of_m(I, L, K) << std::endl;
        std::cout << _bst.pair_include_ancestor_and_descendant_of_m(L, I, K) << std::endl;
    }

    {
        // false
        auto *I = _bst.m_root->rhs;
        auto *L = _bst.m_root->rhs->lhs->rhs->lhs;
        auto *N = _bst.m_root->rhs->lhs->rhs->rhs;

        std::cout << _bst.pair_include_ancestor_and_descendant_of_m(I, L, N) << std::endl;
        std::cout << _bst.pair_include_ancestor_and_descendant_of_m(L, I, N) << std::endl;

        std::cout << _bst.pair_include_ancestor_and_descendant_of_m(I, L, _bst.m_root) << std::endl;
        std::cout << _bst.pair_include_ancestor_and_descendant_of_m(L, I, _bst.m_root) << std::endl;
    }

    return 0;
}