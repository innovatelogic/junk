#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <string>
#include <sstream> 

enum class EOperation
{
    None,
    Mult,
    Div,
    Plus,
    Minus
};

EOperation chToOp(char op)
{
    switch(op)
    {
        case '*':
            return EOperation::Mult;
        break;

        case '/':
            return EOperation::Div;
        break;

        case '+':
            return EOperation::Plus;
        break;

        case '-':
            return EOperation::Minus;
        break;
    }
    return EOperation::None;
}

std::string opToStr(EOperation op)
{
    switch(op)
    {
        case EOperation::Mult:
            return "*";
        break;

        case EOperation::Div:
            return "/";
        break;

        case EOperation::Plus:
            return "+";
        break;

        case EOperation::Minus:
            return "-";
        break;
    }
    return "";
}

bool operator<(EOperation lhs, EOperation rhs)
{
    int rank_lhs = (lhs == EOperation::Mult || lhs == EOperation::Div) ? 2 
                    : (lhs == EOperation::Plus || lhs == EOperation::Minus ? 1 : 5);

    int rank_rhs = (rhs == EOperation::Mult || rhs == EOperation::Div) ? 2 
                    : (rhs == EOperation::Plus || rhs == EOperation::Minus ? 1 : 5);
    return rank_lhs < rank_rhs;
}

class combiner
{
public:

    combiner(int v)
    : m_last_op(EOperation::None)
    {
        m_dq_out.push_back(std::to_string(v));
    }

    void add(int val, EOperation op)
    {

        bool gr_op = m_last_op < op;

        if (gr_op){
            m_dq_out.push_front("(");
        }

        m_dq_out.push_back((gr_op ? ") " : " ") + opToStr(op) + " " + std::to_string(val));

        m_last_op = op;
    }

    std::deque<std::string> m_dq_out;

    EOperation m_last_op;
};

int main()
{
    int x, steps;

    std::cin >> x;
    std::cin >> steps;

    combiner cmb(x);

    while (steps)
    {
        char op;
        int val;

        std::cin >> op >> val;

        cmb.add(val, chToOp(op));

        --steps;
    }

    for (auto const &i : cmb.m_dq_out){
        std::cout << i;
    }

    return 0;
}