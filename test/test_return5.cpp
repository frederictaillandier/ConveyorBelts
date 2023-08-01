#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "return5.h"

// testing the most dummy function possible
TEST_CASE("Testing return 5") { CHECK(return5() == 5); }
