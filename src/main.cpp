#include "belt-factory/belt-factory.h"
#include "belt-room/belt-room.h"
#include "luggage/luggage.h"
#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>

int main() {
  BeltFactory beltFactory;
  BeltRoom beltRoom;
  std::shared_ptr<IDisplayer> _displayer = std::make_shared<Displayer>();

  beltFactory.WithDisplayer(_displayer);
  beltFactory.WithSpeed(1);
  beltRoom.AddBelt(beltFactory.Build());
  beltRoom.AddBelt(beltFactory.Build());
  beltRoom.AddBelt(beltFactory.Build());
  beltRoom.AddBelt(beltFactory.WithSpeed(2).Build());

  beltRoom.BuildBeltRoom();

  beltRoom.EventLoop();
  return 0;
}