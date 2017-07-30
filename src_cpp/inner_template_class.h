
#pragma once

#include "defexport.h"

template<class T>
class JUNK_EXPORT Holder
{
    template<class U>
    class JUNK_EXPORT State
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
