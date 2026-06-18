#include "doctest.h"
#include "water_seven.h"

TEST_CASE("test_401")
{
    char character[FIXED_CHARACTER][MAX_NAME] = {
        "Luffy", "Zoro", "Nami", "Usopp", "Sanji", "Chopper", "Robin"};
    int hp[FIXED_CHARACTER] = {100, 95, 80, 70, 90, 85, 75};
    int skill[FIXED_CHARACTER] = {90, 92, 88, 75, 91, 86, 99};

    int conflictIndex = 120;
    int repairCost = 1500;

    char cipherText[] = "AQ 7XK#96";
    char resultText[500];

    decodeCP9Message(character, hp, skill,
                     conflictIndex, repairCost,
                     cipherText, resultText);

    CHECK(strcmp(resultText, "CP9 IS_TRUE") == 0);
}

TEST_CASE("test_402")
{
    char character[FIXED_CHARACTER][MAX_NAME] = {
        "Luffy", "Zoro", "Nami", "Usopp", "Sanji", "Chopper", "Robin"};
    int hp[FIXED_CHARACTER] = {100, 95, 80, 70, 90, 85, 75};
    int skill[FIXED_CHARACTER] = {90, 92, 88, 75, 91, 86, 99};

    int conflictIndex = 120;
    int repairCost = 1500;

    char cipherText[] = "AQ 7XK#00";
    char resultText[500] = "votien";

    decodeCP9Message(character, hp, skill,
                     conflictIndex, repairCost,
                     cipherText, resultText);

    CHECK(strcmp(resultText, "") == 0);
}

TEST_CASE("test_403")
{
    char character[FIXED_CHARACTER][MAX_NAME] = {
        "Luffy", "Zoro", "Nami", "Usopp", "Sanji", "Chopper", "Robin"};
    int hp[FIXED_CHARACTER] = {100, 95, 80, 70, 90, 85, 75};
    int skill[FIXED_CHARACTER] = {90, 92, 88, 75, 91, 86, 99};

    int conflictIndex = 1;
    int repairCost = 1;

    char cipherText[] = "HELLO#72";
    char resultText[500];

    decodeCP9Message(character, hp, skill,
                     conflictIndex, repairCost,
                     cipherText, resultText);
    CHECK(strcmp(resultText, "MJJCF_FALSE") == 0);
}