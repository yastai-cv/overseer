#include <gtest/gtest.h>


TEST(OverseerTest, Signal)
{
    // Test some functions from the project headers
    ASSERT_EQ(42, 42);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
