#include <gtest/gtest.h>

#include <seastar/core/app-template.hh>
#include <iostream>

namespace junk {

int test_seastar()
{
    seastar::app_template app;

    int argc = 0;
    char** argv = nullptr;


    return app.run(argc, argv, [] {
        std::cout << "Hello seastar!" << std::endl;
        return seastar::make_ready_future<>();
    });

}

TEST(Seastar, Test1)
{
    seastar::app_template app;

    int result = app.run(0, nullptr, [] {
        std::cout << "Hello Seastar!" << std::endl;
        return seastar::make_ready_future<>();
    });

    ASSERT_EQ(result, 0);
}

}