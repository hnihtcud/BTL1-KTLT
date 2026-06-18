#include "doctest.h"
#include "water_seven.h"

TEST_CASE("test_301")
{
    char character[FIXED_CHARACTER][MAX_NAME] = {
        "LUFFY", "ZORO", "SANJI", "NAMI",
        "CHOPPER", "USOPP", "ROBIN"};

    int hp[FIXED_CHARACTER] = {500, 401, 402, 403, 404, 280, 405};
    int skill[FIXED_CHARACTER] = {95, 20, 10, 15, 25, 50, 30};

    int conflictIndex = 120;
    int repairCost = 1500;

    char duel[FIXED_CHARACTER][MAX_NAME];

    resolveDuel(character, hp, skill, conflictIndex, repairCost, duel);

    // Tính U:
    // U = 50 + 120/20 + 1500/500 = 50 + 6 + 3 = 59
    // Luffy = 95 >= 59 → không cần ai hỗ trợ
    // → tập tối ưu là tập rỗng

    for (int i = 0; i < FIXED_CHARACTER; i++)
    {
        CHECK(duel[i][0] == '\0');
    }
}

TEST_CASE("test_302")
{
    char character[FIXED_CHARACTER][MAX_NAME] = {
        "LUFFY", "ZORO", "SANJI", "NAMI",
        "CHOPPER", "USOPP", "ROBIN"};

    int hp[FIXED_CHARACTER] = {500, 2, 1, 9, 8, 280, 6};
    int skill[FIXED_CHARACTER] = {55, 2, 3, 5, 8, 50, 4};

    int conflictIndex = 120;
    int repairCost = 1500;

    char duel[FIXED_CHARACTER][MAX_NAME];

    resolveDuel(character, hp, skill, conflictIndex, repairCost, duel);

    // Tính U:
    // U = 50 + 120/20 + 1500/500 = 50 + 6 + 3 = 59
    // Luffy = 55 <= 59 → 4 -> ZORO + SANJI: bestCost = 5
    CHECK(strcmp(duel[0], "ZORO") == 0);
    CHECK(strcmp(duel[1], "SANJI") == 0);
}