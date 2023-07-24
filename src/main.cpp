#include <iostream>
#include <thread>
#include <unistd.h>
#include "belt-factory/belt-factory.h"

int main()
{
    auto beltFactory = std::make_unique<BeltFactory>();
    auto belt = beltFactory->withSpeed(2).build();
    (void)belt;
    return 0;
}