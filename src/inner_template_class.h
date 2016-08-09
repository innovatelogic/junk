#pragma once

template<class T>
class Holder
{
    template<class U>
    class State
    {
    public:
        State(Holder<T> *owner);

    private:
        Holder<T> *m_owner;
    };

public:
    Holder();
    ~Holder();

    void CreateState();

private:
    State<T> *m_some_state;
};

#include "inner_template_class.ipp"