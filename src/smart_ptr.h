
/*namespace junk
{
    //----------------------------------------------------------------------------------------------
    //
    //----------------------------------------------------------------------------------------------

     template <class T>
    struct SmartPtrCtrlBlock
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

    template <class T>
    class SmartPtr
    {
    public:
        SmartPtr(T *ptr)
        {
            m_ctrl = new SmartPtrCtrlBlock<T>(ptr);
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
            if (m_ctrl->dec() == 0)
            {
                delete m_ctrl;
            }
        }

        SmartPtr& operator=(const SmartPtr &other)
        {
            if (this != &other)
            {
                if (this->dec() == 0) {
                    delete m_ctrl;
                }

                m_ctrl = other.m_ctrl;
                m_ctrl->inc();
            }
            return this;
        }

        T* operator*()
        {
            return m_ctrl ? m_ctrl->ptr : nullptr;
        }
      
    protected:
    private:
        SmartPtrCtrlBlock<T> *m_ctrl;
    }; 
}
*/