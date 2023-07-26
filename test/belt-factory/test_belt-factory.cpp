#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "belt-factory/belt-factory.h"
#include "doctest.h"

TEST_CASE("Testing BeltFactory") {
    std::unique_ptr<IBeltFactory> beltFactory 
        = std::make_unique<BeltFactory>();

    beltFactory->withSpeed(2);
    auto belt = beltFactory->build();
    std::shared_ptr<IBelt> belt2 = beltFactory->build();
    belt->SetNextBelt(belt2);
    std::this_thread::sleep_for(std::chrono::seconds(11));
    CHECK(belt->GetLuggageNumber() == 0);
}