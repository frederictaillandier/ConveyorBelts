#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>
#include "belt-room/belt-room.h"
#include "luggage/luggage.h"

int main()
{
    BeltRoom beltRoom;
    beltRoom.BuildBeltRoom(4);    
    beltRoom.DropLuggage(std::make_unique<Luggage>());
    std::this_thread::sleep_for(std::chrono::seconds(15));
    return 0;
}