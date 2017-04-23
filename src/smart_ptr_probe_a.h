#pragma once

namespace junk
{
	namespace smart_ptr_probe_a
	{
		template<typename T>
		struct reference_container
		{
			reference_container(T *ptr)
			: strong_ref_count(1)
			, ptr(ptr){}
			
			void inc() { strong_ref_count++; }
			void dec() { strong_ref_count--; }
			
			size_t strong_ref_count;
			T *ptr;
		};
		
		template<typename T>
		class smart_ptr
		{
			public:
				smart_ptr(T *ptr)
				: m_ref_cont(new reference_container<T>(ptr))
				{}
				
				~smart_ptr()
				{
					release();
				}
				
				smart_ptr(const smart_ptr &other)
				{
					if (this != &other)
					{
						release();
						m_ref_cont = other.m_ref_cont;
						m_ref_cont->inc();
					}
				}
				
				smart_ptr& operator=(const smart_ptr &other)
				{
					if (this != &other)
					{
						release();
						m_ref_cont = other.m_ref_cont;
						m_ref_cont->inc();
					}
					return *this;
				}
				
				T* get() { return m_ref_cont->ptr; }
				
				T* operator->() const { return m_ref_cont.ptr; }
				
			protected:
				void release()
				{
					m_ref_cont->dec();
					if (m_ref_cont->strong_ref_count == 0){
						delete m_ref_cont;
					}
				}
			
			private:
				reference_container<T> *m_ref_cont;
		};
	}
}