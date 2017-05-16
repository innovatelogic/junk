#pragma once

namespace junk
{
	namespace cpp_test_code
	{
		class	LinkedDatas
		{
		public:
			void		*Datas;
			LinkedDatas	*pNext;
		};

		class	LinkedDatasMgr
		{
		protected:
			LinkedDatas	*pHead;

		public:
			LinkedDatasMgr() : pHead(nullptr){} // we need to set pointer to null by default 
			~LinkedDatasMgr() {/* Clean();*/} // this class allocates memory internaly but no cleaning on destruction


			void Add(void *pDatas)
			{
				LinkedDatas *pElem = new LinkedDatas();

				pElem->pNext = pHead;
				pElem->Datas = pDatas;

				pHead = pElem;
			}

			void* ExtractFirst()
			{
				// check if list not empty but in current implementation it can contain nullptr as data
				// so throw exception 
				if (!pHead){
					throw std::exception("List is empty"); 
				}
				LinkedDatas *pFirst = pHead;
				pHead = pFirst->pNext;

				void *ret = pFirst->Datas; // copy of data

				delete pFirst; // we need delete allocated memory in Add

				return ret;
			}

			void* ExtractLast()
			{
				// check if list not empty but in current implementation it can contain nullptr as data
				// so throw exception 
				if (!pHead){
					throw std::exception("List is empty"); 
				}

				LinkedDatas *pPrevPrev = 0;
				LinkedDatas *pPrev = 0;
				LinkedDatas *pFirst = pHead;

				while (pFirst)
				{
					pPrevPrev = pPrev;
					pPrev = pFirst;
					pFirst = pFirst->pNext;
				}

				if (!pPrev){
					//return 0; can be misundestood by client of this class is this a data with nullptr or error
					// we can throw exception to distinguish this cases
					throw std::exception("Invalid list data"); 
				}

				if (pPrevPrev)
					pPrevPrev->pNext = 0;
				else
					pHead = 0;

				void *ret = pPrev->Datas; // copy of data 
				delete pPrev; // need delete previously allocated memory

				return ret;
			}
		};

	}
}
