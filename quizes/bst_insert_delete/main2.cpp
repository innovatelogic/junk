#include <iostream>
#include <memory>
#include <stack>

// 14.10

class BST
{
    struct node
    {
        node(int data) : data(data) {}
        int data;
        node *lhs;
        node *rhs;
    };

public:
    bool Insert(int k)
    {
        if (!m_root) {
            m_root = std::make_unique<node>(k);
            return true;
        }

        node *root = m_root.get();
        node *parent = nullptr;

        while (root)
        {
            if (root->data == k)
            {
                return false; // duplicate
            }
            else if (k < root->data){
                parent = root;
                root = root->lhs;
            }
            else 
            {
                parent = root;
                root = root->rhs;
            }
        }

        if (k < parent->data){
            parent->lhs = new node(k);
        }else
        {
            parent->rhs = new node(k);
        }
        return true;
    }

    bool Delete(int k)
    {
        if (!m_root) {
            return false;
        }

        node *root = m_root.get();
        node *parent = nullptr;

        // locate node to delete
        while (root)
        {
            if (root->data == k){
                break;
            }
            else if (k < root->data)
            {
                parent = root;
                root = root->lhs;
            }
            else
            {
                parent = root;
                root = root->rhs;
            }
        }

        // leaf just delete
        if (!root->lhs && !root->rhs)
        {
            if (root == m_root.get())
            {
                m_root.reset();
            }
            else {
                if (parent->lhs == root){
                    parent->lhs = nullptr;
                }
                else
                {
                    parent->rhs = nullptr;
                }
                delete root;
            }

        }
        else 
        {
            node *sub_lhs = root->lhs;
            node *sub_rhs = root->rhs;

            // find min node in right subtree
            node *min_right_parent = root;
            node *min_right = sub_rhs;

            while (min_right)
            {
                if (!min_right->lhs){
                    break;
                }
                min_right_parent = min_right;
                min_right = min_right->lhs;
            }

            root->data = min_right->data;

            if (min_right == root->rhs)
            {
                root->rhs = min_right->rhs;
            }
            else{
                min_right_parent->lhs = min_right->rhs;
            }
            
            delete min_right;

        }

        return true;
    }

    void print()
    {
        std::stack<node*> sstack;

        if (m_root)
        {
            sstack.emplace(m_root.get());

            while (sstack.size())
            {
                auto *top = sstack.top();
                sstack.pop();

                std::cout << "( " << top->data;

                if (top->lhs){
                    sstack.emplace(top->lhs);
                    std::cout << " " << top->lhs->data << " ";
                }

                if (top->rhs){
                    sstack.emplace(top->rhs);
                    std::cout << " " << top->rhs->data;
                }

                std::cout << " )" << std::endl; 
            }
        }
    }

    std::unique_ptr<node> m_root;
};


int main()
{
     BST bst;

    bst.Insert(19);
    bst.Insert(7);
    bst.Insert(43);
    bst.Insert(19);
    bst.Insert(3);
    bst.Insert(11);
    bst.Insert(23);
    bst.Insert(47);
    bst.Insert(2);
    bst.Insert(5);
    bst.Insert(8);
    bst.Insert(17);
    bst.Insert(47);
    bst.Insert(37);
    bst.Insert(53);

    bst.print();
/*
    std::cout << "---- rm : 7" << std::endl;

    bst.Delete(7);

    bst.print();

    std::cout << "---- rm : 43" << std::endl;

    bst.Delete(43);

    bst.print();
*/
    std::cout << "---- rm : root" << std::endl;

    bst.Delete(19);

    bst.print();

    return 0;
}