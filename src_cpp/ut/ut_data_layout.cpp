#include <gtest/gtest.h>
#include <iostream>
#include <cstddef>
#include <windows.h>

#define DATAFIELD_OFFSET(TYPE, FIELD) (uint8_t*)&((TYPE*)nullptr)->FIELD - (uint8_t*)nullptr

namespace junk
{
    namespace data_layout_test
    {
        //----------------------------------------------------------------------------------
        struct foo
        {
            int a;
            int b;
            int c;
        };

        TEST(DataLayout, Test0)
        {
            int offset_a = offsetof(foo, a);
            int offset_b = offsetof(foo, b);
            int offset_c = offsetof(foo, c);

            EXPECT_EQ(offset_a, 0);
            EXPECT_EQ(offset_b, 4);
            EXPECT_EQ(offset_c, 8);

            int size = sizeof(foo);
            std::cout << size << std::endl; // MSVC 12 bytes
        }

        //----------------------------------------------------------------------------------
        // add static data
        struct foo_static
        {
            int a;
            int b;

            static int some_static_data;

            int c;
        };

        TEST(DataLayout, Test1)
        {
            int offset_a = offsetof(foo_static, a);
            int offset_b = offsetof(foo_static, b);
            int offset_c = offsetof(foo_static, c);

            EXPECT_EQ(offset_a, 0);
            EXPECT_EQ(offset_b, 4);
            EXPECT_EQ(offset_c, 8);

            int size = sizeof(foo_static);
            std::cout << size << std::endl; // MSVC 12 bytes
        }

        //----------------------------------------------------------------------------------
        struct foo_pad
        {
            short a;
            int   b;
            short c;
        };

        TEST(DataLayout, Test2)
        {
            int offset_a = offsetof(foo_pad, a);
            int offset_b = offsetof(foo_pad, b);
            int offset_c = offsetof(foo_pad, c);

            EXPECT_EQ(offset_a, 0);
            EXPECT_EQ(offset_b, 4);
            EXPECT_EQ(offset_c, 8);

            int size = sizeof(foo_pad);
            std::cout << size << std::endl; // MSVC 12 bytes
        }

        //----------------------------------------------------------------------------------
        struct A
        {
            short a;
            int b;
        };

        struct B : public A
        {
            short c;
        };

        TEST(DataLayout, Test3)
        {
            int offset_a = offsetof(B, a);
            int offset_b = offsetof(B, b);
            int offset_c = offsetof(B, c);

            EXPECT_EQ(offset_a, 0);
            EXPECT_EQ(offset_b, 4);
            EXPECT_EQ(offset_c, 8);

            int size_a = sizeof(A);
            int size_b = sizeof(B);
            std::cout << size_a << " " << size_b << std::endl; // MSVC 8 - 12 bytes

            uint8_t c_b_offset1 = (uint8_t*)&((B*)nullptr)->c - (uint8_t*)&((A*)nullptr)->b;
            uint8_t c_b_offset2 = (uint8_t*)&((B*)nullptr)->c - (uint8_t*)&((B*)nullptr)->b;

            std::cout << c_b_offset1 << c_b_offset2 << std::endl; // MSVC 4 bytes
        }

        //----------------------------------------------------------------------------------
        struct C
        {
            A a;
            short c;
        };

        TEST(DataLayout, Test4)
        {
            int offset_a = offsetof(C, a.a);
            int offset_b = offsetof(C, a.b);
            int offset_c = offsetof(C, c);

            EXPECT_EQ(offset_a, 0);
            EXPECT_EQ(offset_b, 4);
            EXPECT_EQ(offset_c, 8);

            int size_c = sizeof(C);
            std::cout << size_c << std::endl; // MSVC 12 bytes

            uint8_t c_b_offset1 = (uint8_t*)&((C*)nullptr)->c - (uint8_t*)&((A*)nullptr)->b;
            uint8_t c_b_offset2 = (uint8_t*)&((C*)nullptr)->c - (uint8_t*)&((B*)nullptr)->b;

            std::cout << c_b_offset1 << c_b_offset2 << std::endl; // MSVC 4 bytes
        }


        //----------------------------------------------------------------------------------
        struct IFoo
        {
            virtual void foo() {};

            short a;
            int b;
        };

        struct Foo : public IFoo
        {
            short c;
        };

        TEST(DataLayout, Test5)
        {
            int offset_a = offsetof(Foo, a);
            int offset_b = offsetof(Foo, b);
            int offset_c = offsetof(Foo, c);

            EXPECT_EQ(offset_a, 4);
            EXPECT_EQ(offset_b, 8);
            EXPECT_EQ(offset_c, 12);

            int size_c = sizeof(Foo);
            std::cout << size_c << std::endl; // MSVC 16 bytes
        }

        //----------------------------------------------------------------------------------
        struct IA
        {
            virtual void method1() {};
            virtual bool method2(int b) { return false; };
        };

        struct DerivedC : public IA
        {
            void method1() override
            { 
                std::cout << "DerivedC::method1" << std::endl; 
            }

            bool method2(int b) 
            {
                std::cout << "DerivedC::method1" << std::endl;
                return true; 
            }
        };

        TEST(DataLayout, Test6)
        {
         /*   DerivedC d;

			int* vptr = *(int**)&d;

			// variant 1
			typedef void(*pFun1)(void*);
			typedef bool(*pFun2)(void*, int);

			pFun1 pfun1 = (pFun1)(vptr[0]);
			pFun2 pfun2 = (pFun2)(vptr[1]);

			pfun1(&d);
			bool res = pfun2(&d, 100);
			EXPECT_TRUE(res);

			// variant 2
			DerivedC *pd = &d;
			__asm
			{
				mov ecx, pd
			}

			((void(*)()) vptr[0])();
			res = ((bool(*)(int)) vptr[1])(100);
			EXPECT_TRUE(res);*/
        }

		void hacked_function1(DerivedC *self)
		{
			std::cout << "hacked_function1" << std::endl;
		}

		bool hacked_function2(DerivedC *self, int val)
		{
			std::cout << "hacked_function2" << std::endl;
			return false;
		}

		TEST(DataLayout, Test7)
		{
		/*	DerivedC *ptr = new DerivedC;

			int* vptr = *(int**)ptr;

			HANDLE process = ::GetCurrentProcess();
			DWORD protection = PAGE_READWRITE;
			DWORD oldProtection;

			typedef void(*pFun1)(void*);
			typedef bool(*pFun2)(void*, int);

			pFun1 pfun1 = (pFun1)(vptr[0]);
			pFun2 pfun2 = (pFun2)(vptr[1]);

			bool hooked = false;
			if (::VirtualProtectEx(process, &vptr[0], sizeof(int), protection, &oldProtection))
			{
				*(vptr + 0) = (int)hacked_function1;

				if (::VirtualProtectEx(process, &vptr[0], sizeof(int), oldProtection, &oldProtection)) {
					hooked = true;
				}
			}

			bool hooked2 = false;
			if (::VirtualProtectEx(process, &(vptr[1]), sizeof(int), protection, &oldProtection))
			{
				*(vptr + 1) = (int)&hacked_function2;

				if (::VirtualProtectEx(process, &vptr[1], sizeof(int), oldProtection, &oldProtection)) {
					hooked2 = true;
				}
			}

			ptr->method1();
			ptr->method2(100);

			//delete ptr;
			*/
		}

		//----------------------------------------------------------------------------------
		struct AA
		{
			AA()
			{
				std::cout << *(int**)this << std::endl;
				//foo(); // Invalid call
			}

			/*virtual*/ ~AA()
			{
				std::cout << *(int**)this << std::endl;
			//	foo(); // Invalid call
			}

			//virtual void foo()
			//{
			//}
		};

		struct BB : public AA
		{
			BB()
			{
				std::cout << *(int**)this << std::endl;
				//foo(); // Invalid call
			}

			~BB() 
			{
				std::cout << *(int**)this << std::endl;
				//foo(); // Invalid call
			}

			//void foo() override {}
		};

		TEST(DataLayout, Test8)
		{
			AA *ptr = new BB();
			delete ptr;

			//BB a;
		}
    }
}