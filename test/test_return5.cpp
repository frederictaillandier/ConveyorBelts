#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "return5.h"
#include "doctest.h"

// testing the most dummy function possible
TEST_CASE("Testing return 5") {
  CHECK(return5() == 5);
}
