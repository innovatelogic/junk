#include "node.h"
#include <iostream>

//----------------------------------------------------------------------------------------------
bool DateComparisonNode::Evaluate(const Date &date_left, const std::string &event) const
{
    switch (m_cmp)
    {
    case Comparison::Less:{
        return date_left < m_date;
    }break;

    case Comparison::LessOrEqual:{
        return date_left < m_date || m_date == date_left;
    }break;

    case Comparison::Greater:{
        return m_date < date_left;
    }break;

    case Comparison::GreaterOrEqual:{
        return m_date < date_left || m_date == date_left;
    }break;

    case Comparison::Equal:{
        return m_date == date_left;
    }
    
    case Comparison::NotEqual:
        return !(m_date == date_left);
        break;
    
    default:
        break;
    }
    return false;
}

//----------------------------------------------------------------------------------------------
bool EventComparisonNode::Evaluate(const Date &data, const std::string &event_left) const
{
    //std::cout << "[EventComparisonNode::Evaluate]: " << m_event << std::endl;

    switch (m_cmp)
    {
    case Comparison::Less:{
        return event_left < m_event;
    }break;
    
    case Comparison::LessOrEqual:{
        return event_left <= m_event;
    }

    case Comparison::Greater:{
        return event_left > m_event;
    }

    case Comparison::GreaterOrEqual:{
        return event_left >= m_event;
    }

    case Comparison::Equal:{
        return m_event == event_left;
    }break;
    
    case Comparison::NotEqual:
        return m_event != event_left;
        break;
    
    default:
        break;
    }

    return false;
}

//----------------------------------------------------------------------------------------------
bool LogicalOperationNode::Evaluate(const Date &date, const std::string &event) const
{
    switch (m_op)
    {
    case LogicalOperation::And:
        //std::cout << "[LogicalOperationNode::Evaluate]: AND" << std::endl;
        return m_left->Evaluate(date, event) && m_right->Evaluate(date, event);
    break;
    case LogicalOperation::Or:
        //std::cout << "[LogicalOperationNode::Evaluate]: OR" << std::endl;
        return m_left->Evaluate(date, event) || m_right->Evaluate(date, event);
    break;
    }

    return false;
}