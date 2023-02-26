#include <gtest/gtest.h>
#include "overseer/signal.hpp"


TEST(OverseerTest, Signal)
{
    // Test some functions from the project headers
    ASSERT_EQ(overseer::function1(), 42);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
