#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <pthread.h>
#include <cmath>
#include <mylib/vtk_grid.hpp>

using namespace std;

TEST(Vtk, Test1)
{
    VtkGrid grid;
    int code = grid.FromFile("../../tests/test_grids/ventrical.vtk");
    ASSERT_TRUE(code == 0);
    // ASSERT_TRUE(grid.Format == VtkGrid::FORMAT::UNSTRUCTURED_GRID);
    ASSERT_TRUE(grid.Nodes_count == 1585);
    ASSERT_TRUE(abs(grid.Nodes[1584].Z - (-0.5979695902113643)) < 1e-10);
    ASSERT_TRUE(grid.Cells_count == 5063);
    ASSERT_TRUE(grid.Cells[5062].Indecies.size() == 4);
    ASSERT_TRUE(grid.Cells[5062].Indecies[3] == 909);
    ASSERT_TRUE(grid.Cells[5062].type == 10);
}

// TEST(TestGroupName, Subtest_2)
// {
//     ASSERT_FALSE('b' == 'b');
//     cout << "continue test after failure" << endl;
// }

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}