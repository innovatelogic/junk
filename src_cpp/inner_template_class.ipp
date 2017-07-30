
#include "inner_template_class.h"

//----------------------------------------------------------------------------------------------
template<class T>
template<typename U>
Holder<T>::State<U>::State(Holder<T> *owner)
    : m_owner(owner)
{}

//----------------------------------------------------------------------------------------------
template<class T>
Holder<T>::Holder()
{
    CreateState();
}

//----------------------------------------------------------------------------------------------
template<class T>
Holder<T>::~Holder()
{

}

//----------------------------------------------------------------------------------------------
template<class T>
void Holder<T>::CreateState()
{
    m_some_state = new State<T>(this);
}

