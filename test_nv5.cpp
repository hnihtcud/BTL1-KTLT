#include "doctest.h"
#include "water_seven.h"

TEST_CASE("test_501")
{
    int grid[50][50] = {
        {0, 1, 2},
        {3, -1, 1},
        {2, 1, 0}};

    int rows = 3, cols = 3;

    /*
        Hàng 0: 0 + 1 + 2 = 3
        Hàng 1: 3 + 1 = 4
        Hàng 2: 2 + 1 + 0 = 3
        => maxRowSum = 4

        maxCell = 3

        dangerLimit = 4 + 3 = 7
    */

    int result = analyzeDangerLimit(grid, rows, cols);
    CHECK(result == 7);
}

TEST_CASE("test_502")
{
    int grid[50][50] = {
        {0, 1, 5},
        {1, -1, 1},
        {1, 1, 0}};

    int rows = 3, cols = 3;

    // Đường nhỏ nhất: 0→1→1→1→0 = 3
    CHECK(evaluateRoute(grid, rows, cols, 2) == false);
    CHECK(evaluateRoute(grid, rows, cols, 3) == true);
    CHECK(evaluateRoute(grid, rows, cols, 4) == true);
}