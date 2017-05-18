#pragma once

#include "defexport.h"


//----------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------
template<class CLASS_T>
class JUNK_EXPORT ListElement
{
public:
	ListElement(const CLASS_T &data)
		: m_next(nullptr)
		, m_data(data)
	{}

	CLASS_T& data() { return m_data; }

	const ListElement* next() const { return m_next; }
	ListElement*	   next() { return m_next; }

	void set_next(ListElement *next) { m_next = next; }
private:
	ListElement *m_next;
	CLASS_T m_data;
};

//----------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------
template<class CLASS_T>
class JUNK_EXPORT List
{
	List(const List&) = delete;
	List& operator=(const List&) = delete;

public:
	List()
		: m_head(nullptr)
	{
	}
    //----------------------------------------------------------------------------------------------
    ListElement<CLASS_T>* head() { return m_head; }

	//----------------------------------------------------------------------------------------------
	void InsertFront(const CLASS_T &data)
	{
		InsertFrontImpl(data);
	}

	//----------------------------------------------------------------------------------------------
	void Insert(const CLASS_T &data, const ListElement<CLASS_T> *after)
	{
		InsertAfterImpl(data, after);
	}

    //----------------------------------------------------------------------------------------------
    void Erase(ListElement<CLASS_T> *element)
    {
        EraseImpl(element);
    }

	
protected:
	void InsertFrontImpl(const CLASS_T &data)
	{
		if (m_head == nullptr)
		{
			m_head = new ListElement<CLASS_T>(data);
		}
		else
		{
			ListElement<CLASS_T> *prev_head = m_head;

			m_head = new ListElement<CLASS_T>(data);

			m_head->set_next(prev_head);
		}
	}

	//----------------------------------------------------------------------------------------------
	void InsertAfterImpl(const CLASS_T &data, const ListElement<CLASS_T> *after)
	{
		if (!after)
        {
            InsertFrontImpl(data);
			return;
		}

		if (m_head == nullptr)
		{
			m_head = new ListElement<CLASS_T>(data);
		}
		else
		{
			ListElement<CLASS_T> *elem = m_head;

			while (elem)
			{
				if (elem && elem == after)
				{
					// 0 0 0 1> 0 0 0
					ListElement<CLASS_T> *prev_next = elem->next();

					ListElement<CLASS_T> *new_elem = new ListElement<CLASS_T>(data);

					elem->set_next(new_elem);

					new_elem->set_next(prev_next);

					return;
				}

				elem = elem->next();
			}
		}
	}

    //----------------------------------------------------------------------------------------------
    void EraseImpl(ListElement<CLASS_T> *element)
    {
        if (m_head && element)
        {
            if (element == m_head)
            {
                ListElement<CLASS_T> *new_next = element->next();

                delete element;

                m_head = new_next;
            }
            else
            {
                ListElement<CLASS_T> *iter = m_head;

                while (iter)
                {
                    if (iter->next() == element)
                    {
                        //     ^ x
                        // 1 1 1 0 1 1
                        ListElement<CLASS_T> *del_elem = iter->next();

                        ListElement<CLASS_T> *del_next = del_elem->next();

                        delete(del_elem);

                        iter->set_next(del_next);

                        return;
                    }

                    iter = iter->next();
                }
            }
        }
    }

private:
	ListElement<CLASS_T> *m_head;
};


//----------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------
/*void TestList_()
{
    List<int> lst;

    lst.InsertFront(1);
    lst.InsertFront(2);
    lst.InsertFront(3);

    // Ensure 3-2-1

    ListElement<int> *head = lst.head();

    lst.Insert(44, head);

    // Ensure 3-44-2-1

    lst.Erase(lst.head()->next()->next());

    // Ensure 3-44-1

    lst.Erase(lst.head());

    // Ensure 44-1

    lst.Erase(lst.head()->next());

    // Ensure 44

    lst.Erase(lst.head());

    // empty head == null
}*/
