#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <pthread.h>
#include <cmath>

using namespace std;

TEST(VtkParser, Test1)
{
    ASSERT_TRUE(10 == 10);
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