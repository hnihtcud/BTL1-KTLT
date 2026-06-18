#include "doctest.h"
#include "water_seven.h"

TEST_CASE("test_201")
{
    char character[FIXED_CHARACTER][MAX_NAME] = {
        "LUFFY", "ZORO", "SANJI", "NAMI",
        "CHOPPER", "USOPP", "ROBIN"};

    int hp[FIXED_CHARACTER] = {500, 400, 400, 300, 350, 280, 320};
    int skill[FIXED_CHARACTER] = {95, 90, 88, 60, 55, 50, 65};

    int shipHP = 350;
    int repairCost = 1500;

    int result = conflictSimulation(character, hp, skill, shipHP, repairCost);

    // Diễn tiến:
    // Ban đầu: 95-50 + 1500/100 + (500-350)/50 = 45 + 15 + 3 = 63
    // 63 % 6 = 3  → +70  = 133
    // 133 % 6 = 1 → +20  = 153
    // 153 % 6 = 3 → +70  = 223
    // 223 % 6 = 1 → +20  = 243
    // 243 % 6 = 3 → +70  = 313 (dừng)

    CHECK(result == 313);
}