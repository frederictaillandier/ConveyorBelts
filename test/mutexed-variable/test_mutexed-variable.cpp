#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "mutexed-variable/mutexed-variable.h"
#include "doctest.h"

TEST_CASE("Testing MutexedVariable") {
    MutexedVariable<int> mutexedInt = 0;

    CHECK(mutexedInt == 0);
    mutexedInt = 1;
    CHECK(mutexedInt == 1);
}