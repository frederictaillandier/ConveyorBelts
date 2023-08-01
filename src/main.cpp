#include "belt-room/belt-room.h"
#include "luggage/luggage.h"
#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>

int main() {
  BeltRoom beltRoom;
  beltRoom.BuildBeltRoom(4);
  beltRoom.DropLuggage(std::make_unique<Luggage>());
  beltRoom.EventLoop();
  return 0;
}