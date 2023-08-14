#include <thread>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "belt-factory/belt-factory.h"
#include "belt-room/belt-room.h"
#include "doctest.h"

TEST_CASE("Testing belt room with 3 luggages") {
  BeltRoom beltRoom;

  BeltFactory beltFactory;
  beltFactory.WithSpeed(1);
  beltRoom.AddBelt(beltFactory.Build());
  beltRoom.AddBelt(beltFactory.Build());
  beltRoom.AddBelt(beltFactory.Build());
  beltRoom.BuildBeltRoom();
  beltRoom.AddLuggage(std::make_unique<Luggage>());
  beltRoom.AddLuggage(std::make_unique<Luggage>());
  beltRoom.AddLuggage(std::make_unique<Luggage>());
  std::this_thread::sleep_for(std::chrono::seconds(1));
  CHECK(beltRoom.GetBelt(0).lock()->GetLuggageNumber() == 3);
}

TEST_CASE("Testing belt room moving luggage") {
  BeltRoom beltRoom;
  BeltFactory beltFactory;

  beltFactory.WithSpeed(10);
  beltRoom.AddBelt(beltFactory.Build());
  beltRoom.AddBelt(beltFactory.Build());
  beltRoom.AddBelt(beltFactory.Build());
  beltRoom.BuildBeltRoom();
  beltRoom.AddLuggage(std::make_unique<Luggage>());
  std::this_thread::sleep_for(std::chrono::seconds(2));
  CHECK(beltRoom.GetBelt(0).lock()->GetLuggageNumber() == 0);
  CHECK(beltRoom.GetBelt(1).lock()->GetLuggageNumber() == 1);
}