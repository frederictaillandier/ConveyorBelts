#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "belt/belt.h"

TEST_CASE("Testing Belt") {
  std::unique_ptr<IBelt> belt = std::make_unique<Belt>();

  CHECK(belt->GetBeltPosition() <= 0.1f);
  sleep(2);
  CHECK(belt->GetBeltPosition() >= 2);
}

TEST_CASE("Testing Belt Pause/Resume") {
  std::unique_ptr<IBelt> belt = std::make_unique<Belt>();
  belt->Pause();
  sleep(2);
  CHECK(belt->GetBeltPosition() <= 0.1f);
  belt->Resume();
  sleep(2);
  CHECK(belt->GetBeltPosition() >= 2);
}

