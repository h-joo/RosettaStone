#include "gtest/gtest.h"
#include <Utils/TestUtils.h>

#include <Tasks/BasicTasks/SwapPlayerTask.h>

using namespace Hearthstonepp;

TEST(SwapPlayerTask, GetTaskID)
{
    BasicTasks::SwapPlayerTask init;
    EXPECT_EQ(init.GetTaskID(), +TaskID::SWAP);
}

TEST(SwapPlayerTask, Run)
{
    BasicTasks::SwapPlayerTask init;
    TestUtils::PlayerGenerator gen(CardClass::DRUID, CardClass::ROGUE);

    gen.player1.id = 'a';
    gen.player2.id = 'b';

    MetaData result = init.Run(gen.player1, gen.player2);
    EXPECT_EQ(result, MetaData::SWAP_SUCCESS);
    EXPECT_EQ(gen.player1.id, 'b');
    EXPECT_EQ(gen.player2.id, 'a');
}
