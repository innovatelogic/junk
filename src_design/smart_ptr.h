#pragma once

#include "defexport.h"

namespace junk
{
    //----------------------------------------------------------------------------------------------
    //
    //----------------------------------------------------------------------------------------------

    template <class T>
    struct DESIGN_EXPORT SmartPtrCtrlBlock
    {
        T *ptr;
        int counter;

        SmartPtrCtrlBlock(T *p)
            : ptr(p)
            , counter(1){}

        int count() const { return counter; }
        int inc() { return ++counter; }
        int dec() { return --counter; }
    };

    //----------------------------------------------------------------------------------------------
    //
    //----------------------------------------------------------------------------------------------

    template <class T, class T_CTRL = SmartPtrCtrlBlock<T> >
    class DESIGN_EXPORT SmartPtr
    {
    public:
        SmartPtr(T *ptr)
        {
            m_ctrl = new T_CTRL(ptr);
        }

        SmartPtr(T_CTRL *ctrl)
        {
            m_ctrl = ctrl;
        }

        SmartPtr(const SmartPtr &source)
        {
            if (&source != this)
            {
                m_ctrl = source->m_ctrl;
                m_ctrl->inc();
            }
        }

        ~SmartPtr()
        {
            remove();
        }

        SmartPtr& operator=(const SmartPtr &other)
        {
            if (this != &other)
            {
                remove();

                m_ctrl = other.m_ctrl;
                m_ctrl->inc();
            }
            return *this;
        }

        T* operator*()
        {
            return m_ctrl ? m_ctrl->ptr : nullptr;
        }

        void remove()
        {
            m_ctrl->dec();
            if (m_ctrl->count() == 0)
            {
                delete m_ctrl;
                m_ctrl = nullptr;
            }
        }
      
    protected:
    private:
        T_CTRL *m_ctrl;
    }; 
}
