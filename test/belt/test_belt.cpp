#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "belt/belt.h"

TEST_CASE("Testing Belt") {
  std::unique_ptr<IBelt> belt = std::make_unique<Belt>();

  CHECK(belt->GetBeltPosition() <= 0.1f);
  std::this_thread::sleep_for(std::chrono::seconds(2));
  CHECK(belt->GetBeltPosition() >= 2);
}

TEST_CASE("Testing Belt Pause/Resume") {
  std::unique_ptr<IBelt> belt = std::make_unique<Belt>();
  belt->Pause();
  std::this_thread::sleep_for(std::chrono::seconds(2));
  CHECK(belt->GetBeltPosition() <= 0.1f);
  belt->Resume();
  std::this_thread::sleep_for(std::chrono::seconds(2));
  CHECK(belt->GetBeltPosition() >= 2);
}

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

TEST_CASE("Testing dropping between belts")
{
    std::shared_ptr<IBelt> belt1 = std::make_unique<Belt>();
    std::shared_ptr<IBelt> belt2 = std::make_unique<Belt>();

    belt1->SetNextBelt(belt2);
    belt2->SetPreviousBelt(belt1);
    belt1->DropLuggageBack(std::make_unique<Luggage>());
    std::this_thread::sleep_for(std::chrono::seconds(2));
    CHECK(belt2->GetLuggageNumber() == 1);
    CHECK(belt1->GetLuggageNumber() == 0);
}