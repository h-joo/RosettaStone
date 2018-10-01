#include "gtest/gtest.h"
#include <Utils/TestUtils.h>

#include <Tasks/BasicTasks/DestroyTask.h>

using namespace Hearthstonepp;

TEST(DestroyTask, GetTaskID)
{
    BasicTasks::DestroyTask task(EntityType::EMPTY);
    EXPECT_EQ(task.GetTaskID(), +TaskID::DESTROY);
}

TEST(DestroyTask, Run)
{
    TestUtils::PlayerGenerator gen(CardClass::DRUID, CardClass::ROGUE);
    Player& player1 = gen.player1;
    Player& player2 = gen.player2;

    auto card = TestUtils::GenerateMinionCard("minion1", 1, 1);
    Minion minion(card.get());

    // Destroy Source Minion
    player1.field.emplace_back(&minion);

    BasicTasks::DestroyTask task(EntityType::SOURCE);
    task.source = &minion;

    MetaData result = task.Run(player1, player2);
    EXPECT_EQ(result, MetaData::DESTROY_MINION_SUCCESS);
    EXPECT_EQ(player1.field.size(), static_cast<size_t>(0));

    // Destroy Target Minion
    player2.field.emplace_back(&minion);

    BasicTasks::DestroyTask task2(EntityType::TARGET);
    task2.target = &minion;

    MetaData result2 = task2.Run(player1, player2);
    EXPECT_EQ(result2, MetaData::DESTROY_MINION_SUCCESS);
    EXPECT_EQ(player2.field.size(), static_cast<size_t>(0));

    // Destroy Target Weapon
    Card weaponCard;
    Weapon weapon(&weaponCard);
    player2.hero->weapon = &weapon;

    BasicTasks::DestroyTask task3 = BasicTasks::DestroyTask(EntityType::OPPONENT_WEAPON);

    MetaData result3 = task3.Run(player1, player2);
    EXPECT_EQ(result3, MetaData::DESTROY_WEAPON_SUCCESS);
    EXPECT_EQ(player2.hero->weapon, nullptr);
}
