#include <thread>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "belt-room/belt-room.h"
#include "doctest.h"

TEST_CASE("Testing belt room with 3 luggages")
{
    BeltRoom beltRoom;

    beltRoom.BuildBeltRoom(4);
    beltRoom.DropLuggage(std::make_unique<Luggage>());
    beltRoom.DropLuggage(std::make_unique<Luggage>());
    beltRoom.DropLuggage(std::make_unique<Luggage>());

    CHECK(beltRoom.GetBelt(0).lock()->GetLuggageNumber() == 3);
}

TEST_CASE("Testing belt room moving luggage")
{
    BeltRoom beltRoom;

    beltRoom.BuildBeltRoom(3);
    beltRoom.DropLuggage(std::make_unique<Luggage>());
    std::this_thread::sleep_for(std::chrono::seconds(12));
    CHECK(beltRoom.GetBelt(0).lock()->GetLuggageNumber() == 0);
    CHECK(beltRoom.GetBelt(1).lock()->GetLuggageNumber() == 1);
}