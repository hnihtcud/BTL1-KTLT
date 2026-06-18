#include "doctest.h"
#include "water_seven.h"

TEST_CASE("test_001")
{
    char character[FIXED_CHARACTER][MAX_NAME];
    int hp[FIXED_CHARACTER];
    int skill[FIXED_CHARACTER];
    int shipHP = 0;
    int repairCost = 0;

    bool result = readInput("file_khong_ton_tai.txt",
                            character, hp, skill,
                            shipHP, repairCost);

    CHECK(result == false);
}

TEST_CASE("test_002")
{
    ofstream fout("input2.txt");
    fout << "ZORO 110 90\n";
    fout << "GOING_MERRY 320 1500\n";
    fout << "LUFFY 120 95\n";
    fout << "USOPP 70 50\n";
    fout << "CHOPPER 90 55\n";
    fout << "NAMI 80 60\n";
    fout << "SANJI 105 88\n";
    fout << "ROBIN 85 65\n";
    fout.close();

    char character[FIXED_CHARACTER][MAX_NAME] = {};
    int hp[FIXED_CHARACTER] = {};
    int skill[FIXED_CHARACTER] = {};
    int shipHP = 0;
    int repairCost = 0;

    bool result = readInput("input2.txt",
                            character, hp, skill,
                            shipHP, repairCost);

    CHECK(result == true);

    CHECK(strcmp(character[0], "ZORO") == 0);
    CHECK(strcmp(character[1], "LUFFY") == 0);
    CHECK(strcmp(character[2], "USOPP") == 0);

    CHECK(hp[0] == 110);
    CHECK(skill[0] == 90);

    CHECK(shipHP == 320);
    CHECK(repairCost == 1500);
    remove("input2.txt");
}

TEST_CASE("test_003")
{
    ofstream fout("input3.txt");
    fout << "ZORO -10 101\n";
    fout << "GOING_MERRY 320 1500\n";
    fout << "LUFFY 120 95\n";
    fout << "USOPP 70 50\n";
    fout << "CHOPPER 90 55\n";
    fout << "NAMI 80 60\n";
    fout << "SANJI 105 88\n";
    fout << "ROBIN 85 65\n";
    fout.close();

    char character[FIXED_CHARACTER][MAX_NAME] = {};
    int hp[FIXED_CHARACTER] = {};
    int skill[FIXED_CHARACTER] = {};
    int shipHP = 0;
    int repairCost = 0;

    bool result = readInput("input3.txt",
                            character, hp, skill,
                            shipHP, repairCost);

    CHECK(result == true);

    CHECK(strcmp(character[0], "ZORO") == 0);
    CHECK(hp[0] == 0);
    CHECK(skill[0] == 100);
    remove("input3.txt");
}