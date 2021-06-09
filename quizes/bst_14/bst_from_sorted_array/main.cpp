#include <iostream>
#include <vector>
#include <stack>
#include <assert.h>

// 14.9

struct node
{
    node(int data, node *lhs, node *rhs) : data(data), lhs(lhs), rhs(rhs) {}

    ~node()
    {
        delete lhs;
        delete rhs;
    }

    int data;
    node *lhs;
    node *rhs;
};

// (start, end]
node* alloc(size_t start, size_t end, std::vector<int> &arr)
{
    if (start >= end){
        return nullptr;
    }

    size_t mid = (end + start) / 2;

    return new node(arr[mid], alloc(start, mid, arr), alloc(mid + 1, end, arr));
}

void print(node *root)
{
    std::stack<node*> st;

    st.push(root);

    while (st.size())
    {
        node *top = st.top();

        assert(top);

        st.pop();

        std::cout << "(" << top->data;

        if (top->lhs) {
            st.push(top->lhs);
            std::cout << " " << top->lhs->data;
        }

        if (top->rhs) {
            st.push(top->rhs);
            std::cout << " " << top->rhs->data;
        }
        std::cout << ")" << std::endl;
    }
}

int main()
{
    std::vector<int> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    node *root = alloc(0, arr.size(), arr);

    std::cout << "print : " << std::endl;

    print(root);

    delete root;

    return 0;
}