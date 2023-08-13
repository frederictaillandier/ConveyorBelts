#include "belt-room/belt-room.h"
#include "luggage/luggage.h"
#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>

int main() {
  BeltRoom beltRoom;
  beltRoom.BuildBeltRoom(BeltRoom::BELT_NUMBER);
  beltRoom.EventLoop();
  return 0;
}