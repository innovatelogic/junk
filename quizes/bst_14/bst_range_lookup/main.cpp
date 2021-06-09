#include <iostream>
#include <stack>

struct Interval
{
    int min;
    int max;
};

struct Node
{
    Node(int data)
    : data(data)
    {}

    ~Node()
    {
        std::cout << "~dtor: " << data << std::endl;

        delete lhs;
        delete rhs;
    }

    void add(int value)
    {
        if (value < data)
        {
            if (!lhs){
                lhs = new Node(value);
            }
            else {
                lhs->add(value);
            }
        }
        else
        {
            if (!rhs){
                rhs = new Node(value);
            }
            else {
                rhs->add(value);
            }
        }
    }

    void range_lookup(const Interval &interval)
    {
        if (interval.min <= data && data <= interval.max) {

            std::cout << "in: " << data << std::endl;

            if (lhs) {
                lhs->range_lookup({interval.min, data});
            }

            if (rhs) {
                rhs->range_lookup({data, interval.max});
            }
        }
        else if (data < interval.min)
        {
            if (rhs) {
                rhs->range_lookup(interval);
            }
        }
        else if (data > interval.max)
        {
            if (lhs) {
                lhs->range_lookup(interval);
            }
        }


    }

    Node *lhs;
    Node *rhs;

    int data;
};


class BST
{
public:
    BST()
    : root(nullptr)
    {}

    ~BST()
    {
        delete root;
    }

    BST& add(int value)
    {
        if (!root)
        {
            root = new Node(value);
        }
        else
        {
            root->add(value);
        }
        return *this;
    }

    void range_lookup(const Interval &interval)
    {
        if (root)
        {
            root->range_lookup(interval);
        }
    }

    void print()
    {
        std::stack<Node*> sstack;

        if (root)
        {
            sstack.emplace(root);

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

protected:

private:
    Node *root;

};

int main()
{
    BST bst;

    bst.add(19).add(7).add(43).add(3).add(11).add(23).add(47).add(2).add(5).add(17).add(37).add(53).add(13).add(29).add(41).add(41).add(31);

    //bst.print();

    bst.range_lookup({16, 31});
}