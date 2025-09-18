#include <iostream>
#include <seastar/core/app-template.hh>

int main(int argc, char ** argv)
{
    seastar::app_template app;

    int result = app.run(argc, argv, [] {
        std::cout << "Hello Seastar!" << std::endl;
        return seastar::make_ready_future<>();
    });

    return 0;
}