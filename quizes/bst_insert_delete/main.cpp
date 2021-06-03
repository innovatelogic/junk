#include <iostream>
#include <memory>
#include <stack>

class BST
{
    struct node
    {
        node(int data) : data(data) {}
        int data;
        node *lhs = nullptr;
        node *rhs = nullptr;
    };

public:
    bool Insert(int key)
    {
        bool result = false;

        if (!m_root){
            m_root = new node(key);
            result = true;
        }
        else
        {
            node *root = m_root;
            while (1)
            {
                if (root->data == key){
                    break;
                }
                else if (key < root->data) //go to lhs
                {
                    if (!root->lhs) { // no left node - add
                        root->lhs = new node(key);
                        result = true;
                        break;
                    }
                    root = root->lhs;
                }
                else // got to rhs
                {
                    if (!root->rhs){
                        root->rhs = new node(key);
                        result = true;
                        break;
                    }
                    root = root->rhs;
                }
            }
        }

        return result;
    }

    bool Delete(int key)
    {
        bool result = false;

        if (!m_root){
            return false;
        }

        node *parent = nullptr;
        node *root = m_root;

        while (root)
        {
            if (root->data == key)
            {
                node *sub_left = root->lhs;
                node *sub_right = root->rhs;

                node *to_reattach = (sub_right) ? sub_right->lhs : nullptr;

                delete root;

                if (parent)
                {
                    parent->lhs = sub_right;
                    sub_right->lhs = sub_left;
                }
                else {
                    m_root = sub_right;
                    m_root->lhs = sub_left;
                }

                root = sub_right; // sub_right new root

                // find node to reattach subtree (most right of left node)
                if (!root->lhs)
                {
                    root->lhs = to_reattach;
                }
                else
                {
                    node *find = root->lhs;
                    while (find->rhs){
                        find = find->rhs;
                    }
                    find->lhs = to_reattach;
                }
                result = true;
                break;
            }
            else if (key < root->data)
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

        return result;
    }

    void print()
    {
        std::stack<node*> sstack;

        if (m_root)
        {
            sstack.emplace(m_root);

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

    node *m_root = nullptr;
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
    bst.Insert(42);
    bst.Insert(53);

    bst.print();

   /* std::cout << "---- rm : 7" << std::endl;

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