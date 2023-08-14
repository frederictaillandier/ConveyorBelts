#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "belt-factory/belt-factory.h"
#include "belt/belt.h"
#include "doctest.h"

TEST_CASE("Testing Belt next/previous") {
  std::weak_ptr<IBelt> weakBelt;
  {
    std::shared_ptr<IBelt> belt1 = std::make_unique<Belt>();
    std::shared_ptr<IBelt> belt2 = std::make_unique<Belt>();

    weakBelt = belt1;
    belt1->SetNextBelt(belt2);
    belt2->SetPreviousBelt(belt1);
    CHECK(weakBelt.lock() == belt1);
  }
  CHECK(weakBelt.lock() == nullptr);
}

TEST_CASE("Testing Get Id") {
  Belt belt1;

  CHECK(belt1.GetId() == 0);
}

TEST_CASE("Testing pause/resume") {
  BeltFactory beltFactory;
  beltFactory.WithSpeed(10);
  auto belt = beltFactory.Build();

  belt->Pause();
  belt->DropLuggageBack(std::make_unique<Luggage>());
  CHECK(belt->GetLuggageNumber() == 0);
  belt->Resume();
  std::this_thread::sleep_for(std::chrono::seconds(2));
  CHECK(belt->GetLuggageNumber() == 1);
}

TEST_CASE("Testing dropping between belts") {
  std::shared_ptr<IBelt> belt1 = std::make_unique<Belt>();
  std::shared_ptr<IBelt> belt2 = std::make_unique<Belt>();

  belt1->SetNextBelt(belt2);
  belt2->SetPreviousBelt(belt1);
  belt1->DropLuggageFront(std::make_unique<Luggage>());
  std::this_thread::sleep_for(std::chrono::seconds(12));

  CHECK(belt1->GetLuggageNumber() == 0);
  CHECK(belt2->GetLuggageNumber() == 1);
}