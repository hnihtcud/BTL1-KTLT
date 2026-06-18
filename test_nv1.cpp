#include "doctest.h"
#include "water_seven.h"

TEST_CASE("test_101")
{
    int shipHP = 411;
    int repairCost = 253;

    int result = damageEvaluation(shipHP, repairCost);

    CHECK(result == 380);
}

TEST_CASE("test_102")
{
    int shipHP = 456;
    int repairCost = 253;

    int result = damageEvaluation(shipHP, repairCost);

    CHECK(result == 253);
}

TEST_CASE("test_103")
{
    int shipHP = 400;
    int repairCost = 253;

    int result = damageEvaluation(shipHP, repairCost);

    CHECK(result == 253);
}