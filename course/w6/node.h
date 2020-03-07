#pragma once

#include "date.h"
#include <string>

enum class Comparison : size_t
{
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual,
};

enum class LogicalOperation : size_t
{
    And,
    Or
};

//----------------------------------------------------------------------------------------------
class Node
{
public:
    virtual bool Evaluate(const Date &date, const std::string &event) const = 0; //{ return true; }
};

//----------------------------------------------------------------------------------------------
class EmptyNode : public Node
{
public:
    bool Evaluate(const Date &date, const std::string &event) const override { return true; }
};

//----------------------------------------------------------------------------------------------
class DateComparisonNode : public Node
{
public:
    DateComparisonNode(Comparison &cmp, const Date &date)
    : m_cmp(cmp)
    , m_date(date)
    {}

    bool Evaluate(const Date &date, const std::string &event) const override;

private:
    Comparison m_cmp;
    Date m_date;
};

//----------------------------------------------------------------------------------------------
class EventComparisonNode : public Node
{
public:
    EventComparisonNode(Comparison &cmp, const std::string &event)
    : m_cmp(cmp)
    , m_event(event)
    {}

    bool Evaluate(const Date &date, const std::string &event) const override;

private:
    Comparison m_cmp;
    const std::string m_event;
};

//----------------------------------------------------------------------------------------------
class LogicalOperationNode : public Node
{
public:
    LogicalOperationNode(LogicalOperation op, const std::shared_ptr<Node> &left, const std::shared_ptr<Node> &right)
    : m_op(op)
    , m_left(left)
    , m_right(right)
    {}

    bool Evaluate(const Date &data, const std::string &event) const override;

private:
    LogicalOperation m_op;
    std::shared_ptr<const Node> m_left, m_right;
};