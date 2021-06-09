#include <iostream>
#include <vector>
#include <memory>

std::shared_ptr<int> foo()
{
    auto elts = {0, 1, 2, 3, 4};
    std::shared_ptr<std::vector<int>> pvec = std::make_shared<std::vector<int>>(elts);

    return std::shared_ptr<int>(pvec, &(*pvec)[2]);
}

int main()
{
    std::shared_ptr<int> ptr = foo();

    for (int i = -2; i < 3; ++i){
        std::cout << ptr.get()[i] << std::endl;
    }

    return 0;
}