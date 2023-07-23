#include <iostream>
#include <thread>
#include <unistd.h>
#include "belt/belt.h"
#include "belt/ibelt.h"



int main()
{
    std::unique_ptr<IBelt> belt = std::make_unique<Belt>();
    sleep(10);
    return 0;
}