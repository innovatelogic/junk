#include <iostream>


struct node
{
    node(int data, node *next)
    : data(data)
    , next(next){}

    int data;
    node *next;
};

node* find_circular(node *root, node *circular_node)
{
    node *out = nullptr;

    int len = 0;

    {
        node *circular = circular_node;

        do
        {
            ++len;
            circular = circular->next;

        } while (circular != circular_node);
    }

    //std::cout << "len : " << len << std::endl;

    node *p0 = root;
    node *p1 = root;

    do
    {
        p1 = p1->next;
        --len;
    }while (len);

    while (1)
    {
        if (p0 == p1)
        {
            return p0;
        }

        p0 = p0->next;
        p1 = p1->next;
    }

    return out;
}


node *is_circular(node *root)
{
    node *out = nullptr;

    if (root)
    {
        node *slow = root->next;
        node *fast = (slow) ? slow->next : nullptr;

        while (fast)
        {
            if (slow == fast)
            {
                out = find_circular(root, slow);
                break;
            }

            slow = slow->next;
            fast = (fast->next) ? fast->next->next : nullptr;
        }
    }

    return out;
}


int main()
{
    node *root = new node(0, 
        new node(1, 
            new node(2, 
                new node(3, 
                    new node (4, nullptr)
                    )
                )
            )
        );

    root->next->next->next->next->next = root->next->next->next->next;

    node *_node = is_circular(root);

    if (_node)
    {
        std::cout << "is circular : " << _node->data << std::endl;
    }
    else
    {
        std::cout << "no circular" << std::endl;
    }

    return 0;
}