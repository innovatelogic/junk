#include "cpp.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace thread_pool_probe_a
    {
        namespace A
        {
            void foo()
            {
                std::cout << "foo()" << std::endl;
            }
            void foo2(int i, float f)
            {
                std::cout << "foo2(" << i << ", " << f << ")" << std::endl;
            }
            struct Baz
            {
                void bar()
                {
                    std::cout << "Baz::bar()" << std::endl;
                }
                void bar2(double d, const std::string &str)
                {
                    std::cout << "Baz::bar2(" << d << ", " << str << ")" << std::endl;
                }
            };

            TEST(Cpp, ThreadPool_probe_a)
            {
                ThreadPool pool;

                Baz* pBaz = new Baz();
                Baz baz;

                std::function<void(int, int)> myFn = [&](int a, int b)
                {
                    std::cout << "functor(" << a << ", " << b << ")" << std::endl;
                };

                // Вызов простой функции
                pool.runAsync(&foo);

                // Вызов функции с аргументами
                pool.runAsync(&foo2, 100, 54.5f);

                // Вызов метода класса, указатель на класс передаем 2м аргументом
                pool.runAsync(&Baz::bar, pBaz);

                // Вызов метода класса с аргументами *
                pool.runAsync(&Baz::bar2, &baz, 400.3, "Hello World!");

                // Вызов лямбда функции
                pool.runAsync([]() { std::cout << "lambda()" << std::endl; });

                // Вызов функтора
                pool.runAsync(myFn, 10, 20);
            }
        }

        namespace B
        {
            double foo()
            {
                return 14.5;
            }

            int sum(int a, int b)
            {
                return a + b;
            }

            TEST(Cpp, ThreadPool_return_probe_a)
            {
                ThreadPool pool;

                std::function<std::string(int, int)> myFn = [&](int a, int b)
                {
                    std::string str = "String = " + std::to_string(a) + " " + std::to_string(b);
                    return str;
                };

                auto r1 = pool.runAsync<double>(&foo);
                auto r2 = pool.runAsync<int>(&sum, 100, 54);
                auto r3 = pool.runAsync<bool>([]() { return true; });
                auto r4 = pool.runAsync<std::string>(myFn, 50, 20);

                while (!r1->ready);  // Ждем результатов
                    std::cout << r1->data << std::endl;
                while (!r2->ready);
                    std::cout << r2->data << std::endl;
                while (!r3->ready);
                    std::cout << r3->data << std::endl;
                while (!r4->ready);
                    std::cout << r4->data << std::endl;
            }
        }
    }
}